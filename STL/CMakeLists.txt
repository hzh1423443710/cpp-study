cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test-STL)

add_executable(specialIterator specialIterator.cpp)
add_executable(algorithm algorithm.cpp)
