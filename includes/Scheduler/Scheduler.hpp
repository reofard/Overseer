#pragma once

#include "Robot/Robot.hpp"

#include "Scheduler/Action/Action.hpp"
#include "Scheduler/Task/Task.hpp"

#include <memory>
#include <string>
#include <map>
#include <utility>

typedef std::pair<std::shared_ptr<Task>, std::shared_ptr<Robot>> MatchInfo;

class Scheduler
{
private:
    // Task - Robot 매칭 정보
    std::map<int, MatchInfo> match_table;

    // 할당 Task 정보
    std::set<std::shared_ptr<Task>> tasks;

    // 수행 중 Action정보
    std::set<std::shared_ptr<ActionNode>> actions;
};