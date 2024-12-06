#include "boost/asio.hpp"
#include "thread"
#include "shared_mutex"
#include "map"
#include "set"
#include "unordered_map"
#include "condition_variable"

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
    int addTimerEvent(std::function<void()> memberFunction);

    // 주기적인 타이머 이벤트 삭제
    void removeTimerEvent(int timerID);

    // 플래그 상태 설정
    void SetFlag(int flag_id);

    // ioContext를 실행하여 비동기 작업을 처리
    void run();

    // 소멸자, 모든 Tread pool의 작업이 끝날 때 까지 대기
    ~EventManager()
    {
        threadPool_.join();
    }

private:
    //생성자, 싱글톤 패턴이기 때문에 생성자는 private
    EventManager() : threadPool_(2)
    {
    }

    // 싱글톤 패턴이기 때문에 복사 및 할당 금지
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

private:
    boost::asio::thread_pool threadPool_; // Boost 스레드 풀

    std::shared_mutex mutex;
    int idCounter;

    std::map<int, std::function<void()>> events;

    std::thread workerThread;
};