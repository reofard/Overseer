#include <memory>
#include <string>
#include <map>
#include <utility>
#include <vector>

class Executor;
class Action;

typedef int match_index;

// Executor와 Action 사이의 매칭 정보를 나타내는 Class
class MatchTable
{
private:
    
    // Matching 정보 생성시 고유 id할당을 위한 Counter
    match_index id_counter;

    // Task - Robot 매칭 정보, 실제로 nullptr이 아니라 실제 Executor 객체가 할당 되어야 해당 매칭 id를 가진 Action 수행가능
    std::map<match_index, std::shared_ptr<Executor>> match_table;

public:
    MatchTable();

    // 실제 로봇을 매칭,
    void matchExecutor(int idx, std::shared_ptr<Executor> executor);

    // 매칭 아이디 생성로직, 서로 다른 로봇이 수행해야 하는 Action은 서로 다른 매칭아이디를 발급받음
    int issueMatchID();

    // 매칭 로봇 조회 함수
    std::shared_ptr<Executor> getMatchedExecutor(match_index idx);
    
};