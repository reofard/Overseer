#include <memory>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <atomic>

class MatchTable;

class Executor;
class Action;

typedef int MatchIDX;
typedef int ActionID;
typedef int ExecutorID;

struct Dependency
{
    const ActionID id;
    std::set<ActionID> parents;
    std::set<ActionID> childs;

    Dependency(const ActionID& id) : id(id) {}
};

class Scheduler
{
private:
    // 로봇-Action 매칭 정보
    std::unique_ptr<MatchTable> match_table;
    // action 입력 queue
    std::mutex input_mtx;
    std::mutex deps_mtx;
    std::list<std::shared_ptr<Action>> input_queue;
    std::list<std::pair<ActionID, ActionID>> dependency_queue;

    // 수행 중 Action정보
    std::set<ActionID> running_actions;
    std::map<ActionID, std::shared_ptr<Action>> actions;

    // Action간 의존관계 자료구조
    std::set<ActionID> deps_root;
    std::map<ActionID, std::shared_ptr<Dependency>> dependencies;


    // Event 발생을 위한 flag
    //Action 의존관계 편집 및 큐에 쌓여있는 Action들 모두 등록
    std::atomic<bool> NEW_ACTION_ADDED{false};      // 새롭게 스케줄링해야 하는 Action이 추가된 경우

    // 준비된 Executor나 Action이 있는경우, Executor-Action 매칭 및 수행 시작
    std::atomic<bool> EXECUTOR_READY{false};        // Executor가 Action 수행을 종료하고, 새롭게 수행해야 할 Action을 확인해야 하는 경우
    std::atomic<bool> ACTION_READY{false};          // 제약사항이 모두 풀려 실행 가능한 Action이 존재하여 Executor를 배정해야 하는 경우

    // 종료된 Action이 생긴 경우, Action map에서 삭제
    std::atomic<bool> ACTION_TO_REMOVE{false};      // 종료된 Action이 존재하여 해당 Action을 지워야 하는 경우

    // Behavior Tree관련
    

public:

    // 스케줄링 할 Action 추가
    void inputTask(std::vector<std::shared_ptr<Action>> actions, std::vector<int> match_info, std::set<std::pair<ActionID, ActionID>> dependencys);
    void addAction(std::vector<std::shared_ptr<Action>> actions, std::vector<int> match_info);

    // 수행할 Action간추리는 함수
    // void Action
};