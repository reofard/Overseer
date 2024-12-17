#include "boost/asio.hpp"
#include "thread"
#include "shared_mutex"
#include "map"
#include "set"
#include "unordered_map"
#include "condition_variable"
#include <iostream>

class EventManager
{
public:
    // 싱글톤 인스턴스 가져오기
    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }


    void submit(std::function<void()> memberFunction);

    // 주기적인 타이머 이벤트 추가
    int addTimerEvent(std::function<void()> memberFunction, std::chrono::duration<float> period);

    // 주기적인 타이머 이벤트 삭제
    void removeTimerEvent(int timerID);

    // ioContext를 실행하여 비동기 작업을 처리
    void start();

    void stop();

    void waitUntilStopped();

    // 소멸자, 모든 Tread pool의 작업이 끝날 때 까지 대기
    ~EventManager()
    {
        if (workerThread.joinable())
        {
            workerThread.join();  // 스레드 종료 대기
        }
        threadPool_.join();
    }

private:
    //생성자, 싱글톤 패턴이기 때문에 생성자는 private
    EventManager();

    // 싱글톤 패턴이기 때문에 복사 및 할당 금지
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

private:
    int count = 0;

    boost::asio::thread_pool threadPool_; // Boost 스레드 풀

    std::mutex mutex;
    int idCounter;

    std::atomic<bool> run_;                      // 워커 스레드 실행 여부 플래그
    std::condition_variable cv_;    // 워커 스레드에서 사용하는 조건 변수

    std::map<int, std::function<void()>> events;
    std::map<int, std::chrono::duration<float>> event_period;
    std::map<int, std::chrono::steady_clock::time_point> event_last_called_time;

    std::thread workerThread;
};