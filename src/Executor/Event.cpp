#include "Executor/Executor.hpp"
#include "Scheduler/Action/Action.hpp"
#include <stdexcept>

void Executor::assign(std::shared_ptr<Action>& action)
{
    if(state != ExecutorState::UNASSIGN)
    {
        throw std::logic_error("This Robot(" + std::to_string(id) + ") is not assignable");
    }
    
    this->action = action;
    state = ExecutorState::ASSIGN;
}
void Executor::setReady()
{
    if(state != ExecutorState::ASSIGN)
    {
        throw std::logic_error("This Robot(" + std::to_string(id) + ") haven't an action");
    }

    // 로봇이 작업 수행 위치에 도착하여 Action을 받을 수 있는 경우
    action->SetExecutorReady();
    state = ExecutorState::READY;
}
void Executor::PostAction()
{
    if(state != ExecutorState::ASSIGN)
    {
        throw std::logic_error("This Robot(" + std::to_string(id) + ") can not execute any action");
    }

    /* TODO : 로봇에 수행할 액션 보내기 */
    state = ExecutorState::EXECUTION;
}
void Executor::Finish()
{
    this->action.reset();
    state = ExecutorState::UNASSIGN;
}
//구현체