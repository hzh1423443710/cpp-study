cmake_minimum_required(VERSION 3.20)

project(test-designPatterns)

add_subdirectory(./CreationalDesignPatterns)

add_executable(test test.cpp)
add_executable(pimpl ./PIMPL/impl.cpp ./PIMPL/impl.h ./PIMPL/main.cpp)