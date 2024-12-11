#include "Scheduler/MatchTable.hpp"
#include <stdexcept>

MatchTable::MatchTable(): id_counter(0)
{

}


void MatchTable::assignExecutor(int idx, std::shared_ptr<Executor> executor)
{
    // 존재하지 않는 매치정보에 Executor를 할당하려 할 때
    if(match_table.find(idx) == match_table.end())
    {
        throw std::logic_error("Executor(" + std::to_string(1) + ") assignment failed because information " + std::to_string(idx) + " does not exist in the matching table");
    }
    // 이미 로봇이 할당된 매치정보에 Executor를 할당하려 할 때
    if(match_table.at(idx) != nullptr)
    {
        throw std::logic_error("Error that occurred because robot " + std::to_string(1) + " was already assigned to item " + std::to_string(idx) + " of the matching table");
    }

    // 해당 매치정보에 종속된 모든 Action들은 입력받은 Executor가 수행
    match_table[idx] = std::move(executor);

    return;
}

int MatchTable::issueMatchID(ActionId action_id, MatchIdx table_idx)
{
    // 하나의 Action가 두개의 executor에 배정될 수 없기 때문에, 이미 할당된 match info는 재할당 금지
    if(action_2_match.find(action_id) != action_2_match.end())
    {
        throw std::logic_error("This action(" + std::to_string(action_id) + ") already have match_info( " + std::to_string(action_2_match.at(action_id)) + ")");
    }

    // 매치정보 테이블에 아직 매칭정보가 등록되지 않은 액션인경우
    if(table_idx == -1)
    {
        // 매치정보 테이블에 새로운 매치 정보 추가
        table_idx = id_counter++;
        match_table.insert({table_idx, nullptr});
        match_count.insert({table_idx, 0});
    }

    // 이미 해당 인덱스의 매칭정보가 생성된 경우
    else
    {
        match_count[table_idx]++;
    }
    action_2_match.insert({action_id, table_idx});

    return table_idx;
}

void MatchTable::clearAction(ActionId action_id)
{
    //등록되지 않은 Action인 경우 throw error 
    if(action_2_match.find(action_id) == action_2_match.end())
    {
        throw std::logic_error("This action(" + std::to_string(action_id) + ") is not exist.");
    }

    // 삭제하려는 Action이 할당된 매칭정보
    int table_idx = action_2_match.at(action_id);

    // 해당 매칭정보를 사용하는 Action 삭제
    action_2_match.erase(action_id);

    // 해당 매칭정보를 사용하는 action 카운트 감수
    match_count[table_idx]--;
    if(match_count[table_idx] == 0)
    {
        match_count.erase(table_idx);

        //해당 매칭정보를 사용하는 Action이 더이상 존재하지 않는경우
        match_table.erase(table_idx);
    }
}

std::shared_ptr<Executor> MatchTable::getMatchedExecutor(MatchIdx idx)
{
    if(match_table.find(idx) == match_table.end())
    {
        throw std::logic_error("Fail to return Executor because there was no matching information " + std::to_string(idx));
        return nullptr;
    }
    return match_table.at(idx);
}