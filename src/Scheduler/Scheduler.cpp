#include "Scheduler/Scheduler.hpp"
#include "Scheduler/MatchTable.hpp"
#include "Scheduler/Action/Action.hpp"

void Scheduler::addAction(std::vector<std::shared_ptr<Action>> actions)
{
    for(auto& action : actions)
    {
        int id = action->getId();
        this->actions.insert({id, std::move(action)});
    }
}

int Scheduler::addMatchInfo()
{
    return match_table->issueMatchID();
}