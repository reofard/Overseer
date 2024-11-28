#include "Scheduler/Task/Task.hpp"
#include "Scheduler/Action/Action.hpp"

typedef std::shared_ptr<Action> ActionPtr;

// Task생성
Task::Task()
{
    std::map<int, int> id_matcher;
    // 지금은 목업데이터만 생성
    for(int i = 0; i < 3; i++)
    {
        ActionPtr action = std::make_shared<Action>("", "", "");

        id_matcher[i] = action->getId();

        actions.insert({action->getId(), action});
    }
    addActionDependency(id_matcher[0], id_matcher[2]);
    addActionDependency(id_matcher[1], id_matcher[2]);
}

// Task 내부의 Action간 의존관계 추가
void Task::addActionDependency(int parent, int child)
{
    actions[parent]->addChild(actions[child]);
    actions[child]->addParent(actions[parent]);
}

// Action이 끝났을 때 Task 처리(진행사항 기록, 작업 종료 여부 확인)
void Task::finishAction(int id)
{
    actions.at(id)->getHistory();
    actions.erase(id);
}