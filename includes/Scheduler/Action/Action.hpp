#include <string>
#include <memory>
#include <list>

class Task;

// 실제 Action 수행시 필요 정보 구조체
struct ActionData
{
    std::string available_robot_type;   // 수행 로봇 타입
    std::string locaction;                    // 수행 위치
    std::string action;                 // 작업에 필요한 정보
    
    // 기본 생성자
    ActionData() : available_robot_type(""), locaction(""), action("") {}

    // 매개변수를 받는 생성자
    ActionData(const std::string& robot_type, const std::string& loc, const std::string& act)
        : available_robot_type(robot_type), locaction(loc), action(act) {}
};

class Action
{
private:

    // Action 식별자, 초기화 리스트로 action 객체 생성시 초기화
    const int id;

    // 실제 Action 수행시 필요 정보
    ActionData data;

    // 수행 Action 의존관계
    std::list<std::weak_ptr<Action>> parents;
    std::list<std::shared_ptr<Action>> childs;

    // 스케줄러상에서 수행할 로봇의 매칭 정보
    // 0일경우 타입맞는 아무 로봇이나 사용 가능
    int matching_robot_index = 0;

    // 속한 Task 정보
    std::weak_ptr<Task> task;

public:
    
    //의도되지 않은 default 생성자 제거
    Action() = delete;

    // 생성자
    Action(std::string robot_type, std::string loc, std::string action);

    //의존관계 추가
    void addParent(std::shared_ptr<Action> parent);
    void addChild(std::shared_ptr<Action> child);

    //기본 Action 정보 반환
    int getId();
    std::string getType();
    std::string getlocation();
    std::string getExecInfo();

    void getHistory();
};