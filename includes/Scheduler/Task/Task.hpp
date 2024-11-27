#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <set>

class ActionNode;

class Task
{
private:
    // 수행 로봇
    std::vector<std::string> target_robot_type;

    // 소속 Action정보
    std::set<std::shared_ptr<ActionNode>> actions;
};