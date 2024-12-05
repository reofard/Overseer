#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>

class Action;

// 의미론적인 작업의 단위인 Task를 나타내는 class
// 실제 작업 스케줄링 단위는 Action이기 때문에 해당 class는 작업 스케줄링시 사용X
// Monitor객체에서 작업 진행률 및 수행 결과 취합 용 자료구조
class Task
{
private:
    // task 설명
    std::string comment;

    // 수행 로봇
    std::vector<std::string> target_robot_type;

    // 소속 Action정보
    std::map<int, std::shared_ptr<Action>> actions;

public:
    // 생성자
    Task() = delete;
    Task(std::string comment);

    // 소속 Action(감시할 action) 등록 함수
    void addAction(std::shared_ptr<Action>& action);

    // Action이 끝났을 때 Task 처리(진행사항 기록, 작업 종료 여부 확인)
    void finishAction(int id);
};