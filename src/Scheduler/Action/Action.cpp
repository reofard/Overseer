#include "Scheduler/Action/Action.hpp"
#include <string>

Action::Action(std::string robot_type, std::string loc, std::string action) : id(0)
{
    this->data = ActionData(robot_type, loc, action);
}


void Action::addParent(std::shared_ptr<Action> parent)
{
    parents.push_back(parent);
}
void Action::addChild(std::shared_ptr<Action> child)
{
    childs.push_back(child);
}


int Action::getId()
{
    return id;
}
std::string Action::getType()
{
    return data.available_robot_type;
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