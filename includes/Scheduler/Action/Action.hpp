#include <string>
#include <memory>
#include <list>

typedef int match_index;

typedef enum
{
  PENDING,
  MOVING,
  EXECUTING,
  COMPLETED,
} ActionState;

class Task;
class UUID;

// 실제 Action 수행시 필요 정보 구조체
struct ActionData
{
    std::string available_robot_type;   // 수행 로봇 타입
    std::string locaction;              // 수행 위치
    std::string action;                 // 작업에 필요한 정보
    
    // 기본 생성자
    ActionData() = delete;

    // 매개변수를 받는 생성자
    ActionData(const std::string& robot_type, const std::string& loc, const std::string& act)
        : available_robot_type(robot_type), locaction(loc), action(act) {}
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

    // 실제 Action 수행시 필요 정보
    ActionData data;

    // 수행 Action 의존관계
    std::list<std::weak_ptr<Action>> parents;
    std::list<std::shared_ptr<Action>> childs;

    // 해당 Action에 해당하는 매칭테이블의 인덱스
    // 0일경우 타입맞는 아무 로봇이나 사용 가능
    const match_index matching_robot_index;

    // 속한 Task 정보
    std::weak_ptr<Task> task;

public:
    
    //의도되지 않은 default 생성자 제거
    Action() = delete;

    // 생성로직
    // 주어진 데이터에 따른 Action 노드 생성
    Action(std::string robot_type, std::string loc, std::string action, match_index idx);

    // Action간 의존관계 추가 전역 함수
    static void addActionDependency(std::shared_ptr<Action>& parent, std::shared_ptr<Action>& child);
    
    // Action간 Dependency 추가
    void addParent(std::shared_ptr<Action> parent);
    void addChild(std::shared_ptr<Action> child);

    //종료 로직
    // 소멸자 정의, id 및 uuid할당 해제
    ~Action();


    //제어 로직

    //기본 Action 정보 Getter
    int getId();
    std::string getType();
    std::string getlocation();
    std::string getExecInfo();

    void getHistory();
};