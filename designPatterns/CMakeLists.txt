cmake_minimum_required(VERSION 3.20)

project(test-designPatterns)

# -- 创建型
add_subdirectory(./CreationalDesignPatterns)

add_executable(test test.cpp)
# -- PIMPL
add_executable(pimpl ./PIMPL/impl.cpp ./PIMPL/impl.h ./PIMPL/main.cpp)