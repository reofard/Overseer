#include "Scheduler/Scheduler.hpp"
#include "Scheduler/Action/Action.hpp"
#include "Scheduler/Task/Task.hpp"


// Task생성
void Scheduler::createTask()
{
    std::shared_ptr<Task> task = std::make_shared<Task>("목업 테스크");

    std::set<int> id_matcher;
    // 지금은 목업데이터만 생성
    for(int i = 0; i < 3; i++)
    {
        std::shared_ptr<Action> action = std::make_shared<Action>("", "", "");
        int id = action->getId();

        id_matcher.insert(id);

        task->addAction(action);
        actions.insert({id, std::move(action)});
    }
    // addActionDependency(id_matcher[0], id_matcher[2]);
    // addActionDependency(id_matcher[1], id_matcher[2]);
}

// Task 내부의 Action간 의존관계 추가
void Scheduler::addActionDependency(std::shared_ptr<Action>& parent, std::shared_ptr<Action>& child)
{
    parent->addChild(child);
    child->addParent(parent);
}