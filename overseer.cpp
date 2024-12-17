#include <iostream>
#include "Scheduler/Scheduler.hpp"
#include "EventManager/EventManager.hpp"
#include <thread>

Scheduler* scheduler;

int main()
{
    std::cout << "Hello, Overseer!" << std::endl;
    scheduler = new Scheduler();

    EventManager& instance = EventManager::getInstance();
    instance.waitUntilStopped();

    std::cout << "Bye Overseer!" << std::endl;

    return 0;
}