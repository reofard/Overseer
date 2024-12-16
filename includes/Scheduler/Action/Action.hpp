#include <string>
#include <memory>
#include <list>
#include <atomic>

typedef enum
{
  PENDING,
  WAITING,
  EXECUTING,
  TERMINATE,
} ActionState;

class Task;
class Executor;
class UUID;

// 실제 Action 수행시 필요 정보 구조체
struct ActionData
{
    std::string locaction;              // 수행 위치
    std::string action;                 // 작업에 필요한 정보
    
    // 기본 생성자
    ActionData() = delete;

    // 매개변수를 받는 생성자
    ActionData(const std::string& robot_type, const std::string& loc, const std::string& act)
        : locaction(loc), action(act) {}
};

// 작업 스케줄링의 단위인 Action을 나타내는 class
// 해당 클래스 포인터는 Shared pointer로 관리
// 소유주: 스케줄러, Task, 부모 Action
// 스케줄러에서 생성 및 스케줄링, 스케줄링 종료후 포인터 삭제
// Task에서 Task 스케줄링 및 수행 결과 취합 후 포인터 삭제
// 부모 액션이 스케줄링 종료 이후 삭제되면 자동으로 포인터 삭제
// 이 외의 객체가 해당 포인터를 복사해서 갖는 것은 금지
class Action
{
private:

    // Action 식별자, 초기화 리스트로 action 객체 생성시 초기화
    const int id;
    static UUID uuid_converter;

    // 현재 Action의 스케줄링 상태
    ActionState state;

    // 수행을 위한 상태
    std::atomic<bool> action_ready{false};
    std::atomic<bool> executor_ready{false};

    // 실제 Action 수행시 필요 정보
    ActionData data;

    // 수행 할 실제 로봇
    std::weak_ptr<Executor> executor;

    // 속한 Task 정보
    std::weak_ptr<Task> task;

public:
    
    //의도되지 않은 default 생성자 제거
    Action() = delete;

    // 생성로직
    // 주어진 데이터에 따른 Action 노드 생성
    Action(std::string robot_type, std::string loc, std::string action);

    //종료 로직
    // 소멸자 정의, id 및 uuid할당 해제
    ~Action();


    //제어 로직
    // Action 할당
    void assign(std::shared_ptr<Executor>& executor);
    void SetActionReady();
    void SetExecutorReady();
    void ready();
    void Finish();

    //기본 Action 정보 Getter
    int getId();
    ActionState getState();
    std::string getlocation();
    std::string getExecInfo();

    void getHistory();
};