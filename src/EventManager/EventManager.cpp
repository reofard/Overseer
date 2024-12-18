#include "EventManager/EventManager.hpp"

EventManager::EventManager() : threadPool_(1)
{
    start();
}

void EventManager::submit(std::function<void()> memberFunction)
{
    if(!run_) return;
    // 작업을 스레드 풀에 추가
    boost::asio::post(threadPool_, memberFunction);
}

int EventManager::addTimerEvent(std::function<void()> memberFunction, std::chrono::duration<float> period)
{
    std::unique_lock lock(mutex);

    // 새로운 이벤트 ID 생성
    int currentID = idCounter++;
    
    // 이벤트 등록
    events[currentID] = memberFunction;
    event_period[currentID] = period;  // 주기 설정
    event_last_called_time[currentID] = std::chrono::steady_clock::now();  // 마지막 호출 시간 초기화

    return currentID;
}

void EventManager::removeTimerEvent(int flag_id)
{
    std::unique_lock lock(mutex);  // std::mutex로 변경
    events.erase(flag_id);
}

void EventManager::start()
{
    // 스레드 실행 플래그 설정
    run_.store(true);

    workerThread = std::thread([this]() {
        while (run_)
        {
            std::unique_lock lock(mutex);
            auto now = std::chrono::steady_clock::now();

            // 주기적 타이머 이벤트 처리
            for (auto& [id, function] : events)
            {
                auto& lastTime = event_last_called_time[id];
                auto period = event_period[id];

                // 특정 이벤트의 호출 간격(period)이 지났는지 확인
                if (std::chrono::duration<float>(now - lastTime) >= period)
                {
                    submit(function);
                    lastTime = now;  // 마지막 호출 시간 업데이트
                }
            }

            // 조건 변수를 사용해 100ms마다 깨어남
            cv_.wait_for(lock, std::chrono::milliseconds(100));
        }
        threadPool_.join();
    });
}

void EventManager::stop()
{
    run_.store(false);
}

void EventManager::waitUntilStopped()
{
    // workerThread가 종료될 때까지 기다림
    if (workerThread.joinable())
    {
        workerThread.join();
    }
}