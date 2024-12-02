# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

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

# Boost 라이브러리 찾기
set(BOOST_LIBRARY_DIRS "/usr/lib/x86_64-linux-gnu")

# 실행파일 생성
add_executable (overseer
  overseer.cpp

  src/Robot/Robot.cpp

  src/Scheduler/Scheduler.cpp
  src/Scheduler/Action/Action.cpp
  src/Scheduler/Task/Task.cpp
  src/utils/UuidManager.cpp
)

target_compile_options(overseer PUBLIC -Wall -Werror)

# 헤더 파일 경로 설정
target_include_directories(overseer PUBLIC
  ${CMAKE_SOURCE_DIR}/includes
)

# Boost 라이브러리 링크
target_link_libraries(overseer PUBLIC Boost::uuid)