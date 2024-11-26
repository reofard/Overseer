# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

set(CMAKE_BUILD_TYPE Debug)

# 프로젝트 정보
project(
  Overseer          # 프로잭트 이름
  VERSION 0.1
  DESCRIPTION "로봇, 연동설비 관제 서버"
  LANGUAGES CXX)
  
add_executable (overseer
  overseer.cpp
)

target_compile_options(overseer PUBLIC -Wall -Werror)

target_include_directories(overseer PUBLIC ${CMAKE_SOURCE_DIR}/includes)