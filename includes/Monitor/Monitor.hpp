#include <set>
#include <memory>

class Task;

class Monitor
{
private:
    std::set<std::shared_ptr<Task>> tasks;      // 할당 Task 정보
    
public:

    // 수행 과정 tracking 대상 Task 등록
    void addTask(std::shared_ptr<Task> task);
};