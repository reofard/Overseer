#include "Interface/Interface.hpp"

#include "Scheduler/Scheduler.hpp"
#include "Monitor/Monitor.hpp"

#include "Scheduler/Action/Action.hpp"
#include "Scheduler/Task/Task.hpp"

#include <utility>

Interface::Interface(Scheduler* scheduler, Monitor* monitor) : scheduler(scheduler), monitor(monitor)
{
    // 뭐든 하겠지
}

// Task생성, 구조화, 등록 인터페이스
void Interface::createTask()
{
    std::shared_ptr<Task> task = std::make_shared<Task>("목업 테스크");
    std::vector<std::shared_ptr<Action>> actions;

    //목업 데이터
    // std::vector<> action_json;                                   // Action 실제 정보
    std::vector<int> match_info = {0, -1, 0};                       // 실제 Match table상의 매칭 아이디
    std::set<std::pair<int, int>> dependencys= {{0, 2}, {1, 2}};    // Task내부에서 Action간 dependency

    // 지금은 목업데이터만 생성
    for(int i = 0; i < 3; i++)
    {
        //차후 해당 부분은 json에서 파싱
        // int match_id = match_info[i];
        std::string execute_type = "";
        std::string location = "";
        std::string act_data = "";

        std::shared_ptr<Action> action = std::make_shared<Action>(execute_type, location, act_data);

        task->addAction(action);                    // 복사해서 포인터 전달
        actions.emplace_back(std::move(action));    // 이동해서 포인터 전달
    }


    scheduler->inputTask(std::move(actions), std::move(match_info), std::move(dependencys));
    monitor->addTask(std::move(task));
}