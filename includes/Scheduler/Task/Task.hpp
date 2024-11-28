#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>

class Action;

class Task
{
private:
    // 수행 로봇
    std::vector<std::string> target_robot_type;

    // 소속 Action정보
    std::map<int, std::shared_ptr<Action>> actions;

private:

    // 의존관계 생성, task 생성시 에만 사용하기때문에 private
    void addActionDependency(int parent, int child);

public:
    // Task생성
    Task();


    // Action이 끝났을 때 Task 처리(진행사항 기록, 작업 종료 여부 확인)
    void finishAction(int id);
};