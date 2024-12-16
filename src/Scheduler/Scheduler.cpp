#include "Scheduler/Scheduler.hpp"
#include "Scheduler/MatchTable.hpp"
#include "Scheduler/Action/Action.hpp"
#include "Executor/Executor.hpp"
#include <ranges>

void Scheduler::inputExecutor()
{
    std::shared_ptr<Executor> executor = std::make_shared<Executor>("E/V");

    executor_mtx.lock();
    executor_queue.push_back(std::move(executor));
    executor_mtx.unlock();

    NEW_EXECUTOR_ADDED.store(true, std::memory_order_release);
}

void Scheduler::addExecutor()
{
    while(!executor_queue.empty())
    {
        executor_mtx.lock();

        auto executor = std::move(executor_queue.front());
        executor_queue.pop_front();

        executor_mtx.unlock();

        ExecutorID id = executor->getId();
        this->executors.insert({id, std::move(executor)});
    }
}

void Scheduler::inputTask(std::vector<std::shared_ptr<Action>> actions, std::vector<int> match_info, std::set<std::pair<ActionID, ActionID>> dependencys)
{
    
    std::map<int, int> match_set;   // 입력된 매칭정보와 실제로 match table에서 할당받은 매칭정보 관계
    for (size_t i = 0; i < actions.size(); i++)
    {
        // action정보 갖고오기
        auto& action = actions[i];
        auto& match_index = match_info[i];

        // 할당할 아이디 설정
        ActionID id = action->getId();
        MatchIDX issued_id = -1;

        // Action queue에 action 추가
        input_mtx.lock();
        this->input_queue.push_back({std::move(action)});
        input_mtx.unlock();
        
        // 이전에 매칭정보가 발급돠지 않은 action의 경우
        if(match_index != -1 && match_set.find(match_index) == match_set.end())
        {
            // 새롭게 match id발급해서 할당
            issued_id = match_table->issueMatchID(id);

            // 매칭정보 추가
            match_set.insert({match_index, issued_id});
        }
        //action에 할당된 매칭정보가 존재하고 maching table에 등록된 경우
        if(match_index != -1 && match_set.find(match_index) != match_set.end())
        {
            issued_id = match_table->issueMatchID(id, match_set.at(match_index));
        }
        //action에 할당된 매칭정보가 존재하지 않는 경우
        else
        {
            // 어떤로봇이 해도 상관없기 때문에 새롭게 match id발급해서 할당
            // Task내부에서 다른 Action과 수행하는 로봇이 독립적이기 때문에 굳이 match_set에 저장하지 않음
            issued_id = match_table->issueMatchID(id);
        }
    }
    
    for(const auto& [parent, child] : dependencys)
    {
        deps_mtx.lock();
        dependency_queue.emplace_back(actions[parent]->getId(), actions[child]->getId());
        deps_mtx.unlock();
    }

    NEW_ACTION_ADDED.store(true, std::memory_order_release);
}

void Scheduler::addAction()
{
    while(!input_queue.empty())
    {
        input_mtx.lock();

        auto action = std::move(input_queue.front());
        input_queue.pop_front();

        input_mtx.unlock();

        ActionID id = action->getId();
        this->actions.insert({id, std::move(action)});

        // 의존관계 추가
        deps_root.insert(id);
        auto dep = std::make_shared<Dependency>(id);
        dependencies.insert({id, dep});
    }
    while(!dependency_queue.empty())
    {
        deps_mtx.lock();
        auto [parent, child] = std::move(dependency_queue.front());
        dependency_queue.pop_front();
        deps_mtx.unlock();

        // 부모자식관계 추가
        dependencies.at(parent)->childs.insert(child);
        dependencies.at(child)->parents.insert(parent);

        // 자식으로 등록되는 경우 무조건 최상위 노드가 될 수 없음
        if(deps_root.find(child) != deps_root.end())
        {
            deps_root.erase(child);
        }
    }
}

void Scheduler::adjustDependencies()
{
    // TODO : 의존관계 분석 및 의존관계 할당

    // 현재는 그냥 의존관계 해소된 얘들 무조건 ready queue에 추가
    for(auto& [action_id, action] : actions)
    {
        if(action->getState() != ActionState::PENDING)
        {
            continue;
        }
        if(ready_actions.find(action_id) == ready_actions.end())
        {
            ready_actions.insert(action_id);
        }
    }
    // TODO : 의존관계가 해소되지 않아도 먼저 가서 기다려도 되는 작업이면 ready 큐에 넣을 수 있음
    return;
}

void Scheduler::match()
{
    std::map<ActionID, MatchIDX> review_queue;

    for(auto iter = ready_actions.begin(); iter != ready_actions.end(); iter++)
    {
        ActionID action_id = *iter;
        auto& action = actions.at(action_id);

        // 할당 대기중인 작업만 확인
        if(action->getState() != ActionState::PENDING)
        {
            continue;
        }

        int match_idx = match_table->getMatchIdx(action_id);
        std::shared_ptr<Executor> executor = match_table->getMatchedExecutor(match_idx);

        // 아직 수행할 executor가 할당되지 않은 action은 평가 queue에서 잠시 수행 보류
        if(executor == nullptr)
        {
            review_queue.insert({action_id, match_idx});
            continue;
        }

        // executor가 할당은 되었는데, 해당 executor가 다른 action수행중인경우
        if(executor->getState() != ExecutorState::UNASSIGN)
        {
            continue;
        }

        // 수행할 executor가 이미 할당된 경우 바로 수행 시작
        action->assign(executor);
        executor->assign(action);

        // 수행 시작한 action ready큐에서 running큐로 이동
        running_actions.insert(action_id);
        iter = ready_actions.erase(iter);
    }

    // 새로운 Executor를 할당해야하는 Action중 실제로 할당하여 수행 시작 할 로봇 선정
    for(auto iter = review_queue.begin(); iter != review_queue.end(); iter++)
    {
        ActionID action_id = iter->first;
        MatchIDX match_idx = iter->second;
        auto action = actions.at(action_id);
        std::string target_type = match_table->getMatchType(match_idx);

        for(auto iter2 = ready_executors.begin(); iter2 != ready_executors.end(); iter2++)
        {
            const ExecutorID executor_id = *iter2;
            auto executor = executors.at(executor_id);
            std::string executor_type = executor->getType();

            // executor의 타입과 action의 요구 타입이 맞지 않는 경우, 이미 할당된 executor인 경우 스킵
            if(target_type != executor_type) continue;
            if(match_table->isMatched(executor_id)) continue;

            // executor를 match table에 등록
            match_table->assignExecutor(match_idx, executor);

            // 매칭된 action, executor바로 시작
            action->assign(executor);
            executor->assign(action);

            // 수행 시작한 action ready큐에서 running큐로 이동
            running_actions.insert(action_id);
            ready_actions.erase(action_id);
            
            // 수행 시작한 executor ready큐에서 running큐로 이동
            running_executors.insert(executor_id);
            iter2 = ready_executors.erase(iter2);
        }
    }

    return;
}

void Scheduler::refreshExecutors()
{

}
void Scheduler::releaseActions()
{

}