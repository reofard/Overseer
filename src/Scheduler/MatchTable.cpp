#include "Scheduler/MatchTable.hpp"
#include "Executor/Executor.hpp"
#include <stdexcept>

MatchTable::MatchTable(): id_counter(0)
{

}


void MatchTable::assignExecutor(int idx, std::shared_ptr<Executor> executor)
{
    // 할당하려는 Executor id
    const ExecutorId executor_id = executor->getId();

    // 존재하지 않는 매치정보에 Executor를 할당하려 할 때
    if(match_table.find(idx) == match_table.end())
    {
        throw std::logic_error("Executor(" + std::to_string(executor_id) + ") assignment failed because information " + std::to_string(idx) + " does not exist in the matching table");
    }
    // 이미 로봇이 할당된 매치정보에 Executor를 할당하려 할 때
    if(match_table.at(idx) != nullptr)
    {
        throw std::logic_error("Error that occurred because executor(" + std::to_string(executor_id) + ") was already assigned to item " + std::to_string(idx) + " of the matching table");
    }
    // 이미 해당 로봇이 다른 매칭정보에 매칭된 경우
    if(executor_2_match.find(executor_id) != executor_2_match.end())
    {
        throw std::logic_error("Error that occurred because executor(" + std::to_string(executor_id) + ") is already assigned by another match information(" + std::to_string(executor_2_match.at(executor_id)) + ")");
    }

    // 해당 매치정보에 종속된 모든 Action들은 입력받은 Executor가 수행
    executor_2_match[executor_id] = idx;
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

    // 모든 action이 수행완료되고, 해당 매칭 정보를 삭제
    if(match_count[table_idx] == 0)
    {
        //해당 테이블에 로봇이 할당되어있었던 경우
        if(match_table.at(table_idx) != nullptr)
        {
            // 할당되어있던 로봇 id
            int executor_id = match_table.at(table_idx)->getId();

            // 해당 매칭테이블에 할당된 로봇은 있는데, 매칭 정보는 없는경우
            if(executor_2_match.find(executor_id) == executor_2_match.end())
            {
                throw std::logic_error("Match table has this match information(" + std::to_string(table_idx) + ") and executor(" + std::to_string(executor_id) + "), but executor query table has no data.");
            }

            // executor id를 이용한 쿼리테이블에서 데이터 삭제
            executor_2_match.erase(executor_id);
        }
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

std::string MatchTable::getMatchType(MatchIdx idx)
{
    return "";
}

bool MatchTable::isMatched(ExecutorId id)
{
    // 해당 로봇이 아직 매칭 되지 않은지 확인
    if(executor_2_match.find(id) == executor_2_match.end())
    {
        return false;
    }
    return true;
}

MatchIdx MatchTable::getMatchIdx(ActionId idx)
{
    if(action_2_match.find(idx) == action_2_match.end())
    {
        throw std::logic_error("Fail to return Executor because there was no matching information " + std::to_string(idx));
        return -1;
    }
    return action_2_match.at(idx);
}
