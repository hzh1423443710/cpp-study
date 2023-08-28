cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test-hackingcpp LANGUAGES CXX)

add_executable(ascending_seqence ascending_seqence.cpp)
add_executable(bstree bstree/main.cpp bstree/bstree.hpp)
add_executable(prefect_forwarding prefect_forwarding.cpp)
