#include "EventManager/EventManager.hpp"

void EventManager::submit(std::function<void()> memberFunction)
{
    // 작업을 스레드 풀에 추가
    boost::asio::post(threadPool_, [memberFunction]() {
        // 작업 실행
        memberFunction();
    });
}

int EventManager::addTimerEvent(std::function<void()> memberFunction)
{
    std::unique_lock lock(mutex);  // std::mutex로 변경

    // 새로운 이벤트 ID 생성
    events[idCounter] = memberFunction;

    return idCounter++;
}

void EventManager::removeTimerEvent(int flag_id)
{
    std::unique_lock lock(mutex);  // std::mutex로 변경
    events.erase(flag_id);
}

// 플래그 상태 설정
void EventManager::SetFlag(int flag_id)
{
    std::shared_lock lock(mutex);  // std::mutex로 변경
    if (events.find(flag_id) != events.end())
    {
        submit(events.at(flag_id));
    }
}