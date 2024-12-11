#include <memory>
#include <string>
#include <map>
#include <utility>
#include <vector>

class Executor;
class Action;

typedef int MatchIdx;
typedef int ActionId;

// Executor와 Action 사이의 매칭 정보를 나타내는 Class
class MatchTable
{
private:
    
    // Matching 정보 생성시 고유 id할당을 위한 Counter
    MatchIdx id_counter;

    // Task - Robot 매칭 정보, 실제로 nullptr이 아니라 실제 Executor 객체가 할당 되어야 해당 매칭 id를 가진 Action 수행가능
    std::map<MatchIdx, std::shared_ptr<Executor>> match_table;
    std::map<MatchIdx, int> match_count;
    std::map<ActionId, MatchIdx> action_2_match;

public:
    MatchTable();

    // 실제 로봇을 매칭,
    void assignExecutor(int idx, std::shared_ptr<Executor> executor);

    // Action생성에 따른 매칭 아이디 할당 함수
    // 서로 다른 로봇이 수행해야 하는 Action은 서로 다른 매칭아이디를 발급받음
    int issueMatchID(ActionId action_id, MatchIdx table_idx = -1);

    // Action 종료에 따른 매칭 아이디 할당 해제 함수
    void clearAction(ActionId action_id);

    // 매칭 로봇 조회 함수
    std::shared_ptr<Executor> getMatchedExecutor(MatchIdx idx);
    
};