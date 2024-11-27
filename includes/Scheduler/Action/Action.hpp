#pragma once

#include <string>
#include <memory>
#include <list>

class Task;

// 실제 Action 수행시 필요 정보 구조체
struct Action
{
    std::string available_robot_type;   // 수행 로봇 타입
    std::string loc;                    // 수행 위치
    std::string action;                 // 작업에 필요한 정보
};

class ActionNode
{
private:

    // Action 식별자
    std::string id;

    // 실제 Action 수행시 필요 정보
    std::unique_ptr<Action>* action;

    // 수행 Action 의존관계
    std::list<std::weak_ptr<ActionNode>> parents;
    std::list<std::shared_ptr<ActionNode>> childs;

    // 스케줄러상에서 수행할 로봇의 매칭 정보
    // 0일경우 타입맞는 아무 로봇이나 사용 가능
    int matching_robot_index = 0;

    // 속한 Task 정보
    std::weak_ptr<Task> task;
};