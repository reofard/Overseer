#include <string>
#include <memory>
#include <list>

typedef int match_index;

typedef enum
{
  UNASSIGN,
  ASSIGN,
  READY,
  EXECUTION,
} ExecutorState;

class Action;
class UUID;

class Executor
{
private:

    // Action 식별자, 초기화 리스트로 action 객체 생성시 초기화
    const int id = 0;
    static UUID uuid_converter;

    // 현재 Action의 스케줄링 상태
    ExecutorState state;

    // 수행 Action 의존관계
    std::shared_ptr<Action> action;

public:
    
    //의도되지 않은 default 생성자 제거
    // Executor() = delete;

    // 생성로직
    // 주어진 데이터에 따른 Action 노드 생성
    // Executor(std::string robot_type);


    //종료 로직
    // 소멸자 정의, id 및 uuid할당 해제
    // ~Executor();


    //제어 로직
    // Action 할당
    void assign(std::shared_ptr<Action>& action);
    void setReady();
    void PostAction();
    void Finish();

    //기본 Action 정보 Getter
    // int getId();
    // std::string getType();
    // std::string getlocation();
};