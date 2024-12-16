#include "Executor/Executor.hpp"
#include "utils/UuidManager.hpp"

// 생성자
Executor::Executor(std::string robot_type) : id(uuid_converter.issueID()), type(robot_type)
{
    state=UNASSIGN;
}
// 소멸자
Executor::~Executor()
{
    uuid_converter.deleteID(getId());
    action.reset();
}

// Action 정보 함수
int Executor::getId()
{
    return id;
}
ExecutorState Executor::getState()
{
    return state;
}
std::string Executor::getType()
{
    return type;
}