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
    // 기본생성자 제거
    Interface() = delete;

    // 생성자, 외부입력을 넣어줄 스케줄러, 모니터 객체 할당
    Interface(Scheduler* scheduler, Monitor* monitor);

    // 외부로부터 입력받은 데이터 기반으로 Task, action 생성하는 함수
    void createTask();
};