#include <memory>
#include <string>
#include <map>
#include <utility>

class Scheduler;
class Monitor;

class Action;
class Task;

class Interface
{
private:
    Scheduler* scheduler;
    Monitor* monitor;

public:

    // 외부로부터 입력받은 데이터 기반으로 Task, action 생성하는 함수
    void createTask();
};