#include "Scheduler/Action/Action.hpp"
#include "utils/UuidManager.hpp"

UUID Action::uuid_converter;

// 생성자
Action::Action(std::string robot_type, std::string loc, std::string action) : id(uuid_converter.issueID()), data(ActionData("", "", ""))
{
    state=PENDING;
    this->data = ActionData(robot_type, loc, action);
}

// Task 내부의 Action간 의존관계 추가 전역 함수
void Action::addActionDependency(std::shared_ptr<Action>& parent, std::shared_ptr<Action>& child)
{
    parent->addChild(child);
    child->addParent(parent);
}

// Action 부모 관계 추가
void Action::addParent(std::shared_ptr<Action> parent)
{
    parents.push_back(parent);
}

// Action 자식 관계 추가
void Action::addChild(std::shared_ptr<Action> child)
{
    childs.push_back(child);
}


// 소멸자
Action::~Action()
{
    uuid_converter.deleteID(getId());
    executor.reset();
    task.reset();
}


// Action 정보 함수
int Action::getId()
{
    return id;
}
ActionState Action::getState()
{
    return state;
}
std::string Action::getlocation()
{
    return data.locaction;
}
std::string Action::getExecInfo()
{
    return data.action;
}

// Action의 진행사항 반환
void Action::getHistory()
{
    //TODO : 수행 과정 반환
}

// 구현체