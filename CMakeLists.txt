# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.15)

# C++17 표준을 요구
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 배포용 이미지와 devcontainer개발시 빌드버전을 debug와 release로 따로 사용
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_subdirectory(deps/boost EXCLUDE_FROM_ALL)
 

# 프로젝트 정보
project(
  Overseer          # 프로잭트 이름
  VERSION 0.1
  DESCRIPTION "로봇, 연동설비 관제 서버"
  LANGUAGES CXX)

# 실행파일 생성
add_executable (overseer
  overseer.cpp

  # 작업 수행자
  src/Executor/Executor.cpp
  src/Executor/Event.cpp
  
  # 스케줄링
  src/Scheduler/Scheduler.cpp
  src/Scheduler/MatchTable.cpp
  src/Scheduler/Action/Action.cpp
  src/Scheduler/Action/Event.cpp

  # 모니터링
  src/Monitor/Monitor.cpp
  src/Scheduler/Task/Task.cpp

  # 인터페이스
  src/Interface/Interface.cpp

  # UUID발급 유틸
  src/utils/UuidManager.cpp

  # 쓰레드풀기반 이벤트 Executor
  src/EventManager/EventManager.cpp

  # Behavior Tree
  src/utils/BehaviorTree/ActionNode.cpp
  src/utils/BehaviorTree/CompositeNode.cpp
  src/utils/BehaviorTree/DecoratorNode.cpp
  src/utils/BehaviorTree/Selector.cpp
  src/utils/BehaviorTree/Sequence.cpp
)

target_compile_options(overseer PUBLIC -Wall -Werror)

# 헤더 파일 경로 설정
target_include_directories(overseer PUBLIC
  ${CMAKE_SOURCE_DIR}/includes
)

# Boost 라이브러리 링크
target_link_libraries(overseer PUBLIC Boost::uuid Boost::asio)