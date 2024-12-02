#include "Scheduler/Task/Task.hpp"
#include "Scheduler/Action/Action.hpp"

typedef std::shared_ptr<Action> ActionPtr;

// Task생성
Task::Task(std::string comment)
{
    this->comment = comment;
}


void Task::addAction(std::shared_ptr<Action>& action)
{
    int id = action->getId();
    actions.insert({id, action});
}