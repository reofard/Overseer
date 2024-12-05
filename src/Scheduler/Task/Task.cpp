#include "Scheduler/Task/Task.hpp"
#include "Scheduler/Action/Action.hpp"
#include <stdexcept>

typedef std::shared_ptr<Action> ActionPtr;

// Task생성
Task::Task(std::string comment)
{
    this->comment = comment;
}


void Task::addAction(std::shared_ptr<Action>& action)
{
    int id = action->getId();

    if(actions.find(id) != actions.end())
    {
        throw std::logic_error("Action with id" + std::to_string(id) + " already exists");
    }

    actions.insert({id, action});
}