#include <iostream>
#include "Interface/Interface.hpp"
#include "Scheduler/Scheduler.hpp"
#include "Monitor/Monitor.hpp"
#include "EventManager/EventManager.hpp"
#include <thread>

Scheduler* scheduler;
Interface* interface;
Monitor* monitor;

int main()
{
    std::cout << "Hello, Overseer!" << std::endl;
    
    scheduler = new Scheduler();
    monitor = new Monitor();

    interface = new Interface(scheduler, monitor);

    interface->createTask();
    
    EventManager& instance = EventManager::getInstance();
    instance.waitUntilStopped();

    std::cout << "Bye Overseer!" << std::endl;

    return 0;
}