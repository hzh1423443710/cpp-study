cmake_minimum_required(VERSION 3.5)

project(VariadicTemplate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(templateInterface templateInterface.cpp)
add_executable(templateInherit templateInherit.cpp)
add_executable(function function.cpp)
