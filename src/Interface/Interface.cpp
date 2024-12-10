#include "Interface/Interface.hpp"
#include "Scheduler/Scheduler.hpp"
#include "Monitor/Monitor.hpp"

#include "Scheduler/Action/Action.hpp"
#include "Scheduler/Task/Task.hpp"


// Task생성, 구조화, 등록 인터페이스
void Interface::createTask()
{
    std::shared_ptr<Task> task = std::make_shared<Task>("목업 테스크");
    std::vector<std::shared_ptr<Action>> actions;

    // 실제 Match table상의 매칭 아이디
    std::map<int, int> match_set;

    // std::vector<> action_json;
    std::set<std::pair<int, int>> dependencys= {{0, 2}, {1, 2}};
    // 지금은 목업데이터만 생성
    for(int i = 0; i < 3; i++)
    {
        int match_id = -1;
        std::string execute_type = "";
        std::string location = "";
        std::string act_data = "";

        std::shared_ptr<Action> action;

        //Matching Table 정보 생성
        //action에 할당된 매칭정보가 존재하고 maching table에 등록되지 않은경우
        if(false && match_id != -1 && match_set.find(match_id) == match_set.end())
        {
            match_set.insert({match_id, scheduler->addMatchInfo()});
            action = std::make_shared<Action>(execute_type, location, act_data, match_set.at(match_id));

        }
        //action에 할당된 매칭정보가 존재하고 maching table에 등록된 경우
        if(false && match_id != -1 && match_set.find(match_id) != match_set.end())
        {
            action = std::make_shared<Action>(execute_type, location, act_data, match_set.at(match_id));
        }
        //action에 할당된 매칭정보가 존재하지 않는 경우
        else
        {
            action = std::make_shared<Action>(execute_type, location, act_data, scheduler->addMatchInfo());
        }

        task->addAction(action);                    // 복사해서 포인터 전달
        actions.emplace_back(std::move(action));    // 이동해서 포인터 전달
    }

    for(const auto& [parent, child] : dependencys)
    {
        Action::addActionDependency(actions[parent], actions[child]);
    }


    scheduler->addAction(std::move(actions));
    monitor->addTask(std::move(task));
}