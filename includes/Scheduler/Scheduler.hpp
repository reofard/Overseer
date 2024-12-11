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
    void addAction(std::vector<std::shared_ptr<Action>> actions, std::vector<int> match_info);
};