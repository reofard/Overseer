#include "Scheduler/Action/Action.hpp"
#include <stdexcept>

void Action::assign(std::shared_ptr<Executor>& executor)
{
    if(state != ActionState::PENDING)
    {
        throw std::logic_error("This Action(" + std::to_string(id) + ") is not assignable");
    }
    this->executor = executor;
    state = ActionState::WAITING;
}

void Action::setActionReady()
{
    // 해당 로직은 action의 의존관계 여부에 따라 호출되기 때문에,
    // 수행할 로봇이 없어도 Action이 의존관계가 없다면 현재 Action상태에 관계 없이 set 될 수 있음
    
    // 아토믹 객체를 이용하여 병렬적인 transition flag 처리
    action_ready.store(true, std::memory_order_release);

    // 무조건 executor_ready.load는 다른 쓰레드의 executor_ready.store가 실행중이면 잠시 대기후 실행하게 됨
    if(executor_ready.load(std::memory_order_acquire))
    {
        ready();
    }
}

void Action::setExecutorReady()
{
    if(state != ActionState::WAITING)
    {
        throw std::logic_error("This Action(" + std::to_string(id) + ") is not assign state");
    }
    // 아토믹 객체를 이용하여 병렬적인 transition flag 처리
    executor_ready.store(true, std::memory_order_release);

    // 무조건 action_ready.load는 다른 쓰레드의 action_ready.store가 실행중이면 잠시 대기후 실행하게 됨
    if(action_ready.load(std::memory_order_acquire))
    {
        ready();
    }
}


void Action::ready()
{
    state = ActionState::EXECUTING;
    /*TODO : 로봇에 PostAction()함수 호출*/
}

void Action::finish()
{
    if(state != ActionState::EXECUTING)
    {
        throw std::logic_error("This Action(" + std::to_string(id) + ") is not assign state");
    }
    
    this->executor.reset();
    state = ActionState::TERMINATE;

    /*TODO : Scheduler에 Action하나가 종료되어 남는 로봇이 있으니 다시 다음에 수행할 Action스케줄링 하라는 명령 전달*/
}
// 구현체