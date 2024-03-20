cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 惯用手法
project(idiom)

# 奇异递归模板模式
add_executable(crtp ctrp.cpp)
# enable_shared_from_this
add_executable(shared_from_this shared_from_this.cpp)