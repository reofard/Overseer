#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>

class Action;

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

    void addAction(std::shared_ptr<Action>& action);


    // Action이 끝났을 때 Task 처리(진행사항 기록, 작업 종료 여부 확인)
    void finishAction(int id);
};