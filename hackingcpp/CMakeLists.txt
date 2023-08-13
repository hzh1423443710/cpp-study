cmake_minimum_required(VERSION 3.5)

project(hackingcpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ascending_seqence ascending_seqence.cpp)
add_executable(bstree main.cpp bstree.hpp)
add_executable(prefect_forwarding prefect_forwarding.cpp)
add_executable(uniform_distribution uniform_distribution.cpp)
