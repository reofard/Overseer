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

    /*TODO : Path Planner에 goal 입력*/
    // 일단은 로봇이 할당되면 무조건 READY상태로 변경
    // 항상 로봇이 Action이 종료될 때 다음 Action위치에 도착했다고 가정
    setReady();
}
void Executor::setReady()
{
    if(state != ExecutorState::ASSIGN)
    {
        throw std::logic_error("This Robot(" + std::to_string(id) + ") haven't an action");
    }

    // 로봇이 작업 수행 위치에 도착하여 Action을 받을 수 있는 경우
    action->setExecutorReady();
    state = ExecutorState::READY;
}
void Executor::postAction()
{
    if(state != ExecutorState::ASSIGN)
    {
        throw std::logic_error("This Robot(" + std::to_string(id) + ") can not execute any action");
    }

    /* TODO : 로봇에 수행할 액션 보내기 */
    state = ExecutorState::EXECUTION;
}
void Executor::finish()
{
    // 로봇으로부터 작업 종료 메세지를 받아 Action에 전달
    this->action->finish();

    // 할당된 Action이 종료되었으니 Action 할당 해제
    this->action.reset();
    state = ExecutorState::UNASSIGN;
}
//구현체