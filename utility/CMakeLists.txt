cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(utility)

# 日志库
add_executable(myLogger ./logger/logger.h ./logger/logger.cpp ./logger/main.cpp)
if(LINUX)
    target_compile_options(myLogger PRIVATE "-Wall")
endif(LINUX)

