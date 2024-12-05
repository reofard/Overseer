#include <memory>
#include <string>
#include <map>
#include <utility>
#include <vector>

class MatchTable;

class Executor;
class Action;

typedef int match_index;

class Scheduler
{
private:
    std::unique_ptr<MatchTable> match_table;            //로봇-Action 매칭 정보

    std::map<int, std::shared_ptr<Action>> actions;     // 수행 중 Action정보

public:

    // 스케줄링 할 Action 추가
    void addAction(std::vector<std::shared_ptr<Action>> actions);

    // 다른 로봇이 수행해야하는 Action이 존재할 때 매칭 정보 생성 및 id 발급 함수
    int addMatchInfo();

};