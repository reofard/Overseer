#include <memory>
#include <string>
#include <map>
#include <set>
#include <utility>

class Robot;
class Action;
class Task;

typedef std::pair<std::shared_ptr<Task>, std::shared_ptr<Robot>> MatchInfo;

class Scheduler
{
private:

    std::map<int, MatchInfo> match_table;               // Task - Robot 매칭 정보
    std::set<std::shared_ptr<Task>> tasks;              // 할당 Task 정보
    std::map<int, std::shared_ptr<Action>> actions;     // 수행 중 Action정보

public:

    // 입력받는 데이터 기반으로 Task, action 생성
    void createTask();

    // 의존관계 생성, task 생성시 에만 사용하기때문에 private
    void addActionDependency(std::shared_ptr<Action>& parent, std::shared_ptr<Action>& child);

};