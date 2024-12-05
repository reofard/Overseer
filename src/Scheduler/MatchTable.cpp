#include "Scheduler/MatchTable.hpp"
#include <stdexcept>

MatchTable::MatchTable(): id_counter(0)
{

}

int MatchTable::issueMatchID()
{
    match_table.insert({id_counter, nullptr});
    return id_counter++;
}

void MatchTable::matchExecutor(int idx, std::shared_ptr<Executor> executor)
{
    // 존재하지 않는 매치정보에 Executor를 할당하려 할 때
    if(match_table.find(idx) == match_table.end())
    {
        throw std::logic_error("Executor(" + std::to_string(1) + ") assignment failed because information " + std::to_string(idx) + " does not exist in the matching table");
    }
    if(match_table.at(idx) != nullptr)
    {
        throw std::logic_error("Error that occurred because robot " + std::to_string(1) + " was already assigned to item " + std::to_string(idx) + " of the matching table");
    }
    match_table.insert({idx, executor});

    return;
}

std::shared_ptr<Executor> MatchTable::getMatchedExecutor(match_index idx)
{
    if(match_table.find(idx) == match_table.end())
    {
        throw std::logic_error("Fail to return Executor because there was no matching information " + std::to_string(idx));
    }
    return nullptr;
}