#include "Monitor/Monitor.hpp"
#include "Scheduler/Task/Task.hpp"


void Monitor::addTask(std::shared_ptr<Task> task)
{
    tasks.insert(std::move(task));
}