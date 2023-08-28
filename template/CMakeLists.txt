cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test-VariadicTemplate LANGUAGES CXX)

add_executable(templateInterface ./VariadicTemplate/templateInterface.cpp)
add_executable(templateInherit ./VariadicTemplate/templateInherit.cpp)
add_executable(function ./VariadicTemplate/function.cpp)


add_executable(enable_if enable_if.cpp)
add_executable(SFNAE SFNAE.cpp)
add_executable(traits traits.cpp)
add_executable(TypeDeduction TypeDeduction.cpp)

