#include "Scheduler/Scheduler.hpp"
#include "Scheduler/MatchTable.hpp"
#include "Scheduler/Action/Action.hpp"
#include <ranges>

void Scheduler::addAction(std::vector<std::shared_ptr<Action>> actions, std::vector<int> match_info)
{
    std::map<int, int> match_set;   // 입력된 매칭정보와 실제로 match table에서 할당받은 매칭정보 관계
    for (size_t i = 0; i < actions.size(); i++)
    {
        // action정보 갖고오기
        auto& action = actions[i];
        auto& match_index = match_info[i];

        // 할당할 아이디 설정
        ActionID id = action->getId();
        MatchIDX issued_id = -1;

        // Action queue에 action 추가
        this->actions.insert({id, std::move(action)});
        
        // 이전에 매칭정보가 발급돠지 않은 action의 경우
        if(match_index != -1 && match_set.find(match_index) == match_set.end())
        {
            // 새롭게 match id발급해서 할당
            issued_id = match_table->issueMatchID(id);

            // 매칭정보 추가
            match_set.insert({match_index, issued_id});
        }
        //action에 할당된 매칭정보가 존재하고 maching table에 등록된 경우
        if(match_index != -1 && match_set.find(match_index) != match_set.end())
        {
            issued_id = match_table->issueMatchID(id, match_set.at(match_index));
        }
        //action에 할당된 매칭정보가 존재하지 않는 경우
        else
        {
            // 어떤로봇이 해도 상관없기 때문에 새롭게 match id발급해서 할당
            // Task내부에서 다른 Action과 수행하는 로봇이 독립적이기 때문에 굳이 match_set에 저장하지 않음
            issued_id = match_table->issueMatchID(id);
        }
    }
}