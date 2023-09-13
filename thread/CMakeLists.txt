cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test-thread)

# 线程参数拷贝
add_executable(thread_para_transfer ./thread_para_transfer/thread_para_transfer.cpp)
# 并行accumulate
add_executable(parallel_accumulate ./parallel_accumulate/parallel_accumulate.cpp)
# 线程安全队列
add_executable(threadsafe_queue ./threadsafe_queue/threadsafe_queue.hpp ./threadsafe_queue/main.cpp)
# 原子操作
add_executable(atomic_flag ./atomic_flag/main.cpp)
# 读写锁
add_executable(rwlock ./rwlock/main.cpp)
