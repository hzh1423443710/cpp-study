cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test-VariadicTemplate LANGUAGES CXX)

# 变参模板
add_executable(templateInterface ./VariadicTemplate/templateInterface.cpp)
add_executable(templateInherit ./VariadicTemplate/templateInherit.cpp)
add_executable(function ./VariadicTemplate/function.cpp)

# 推导指引
add_executable(TypeDeduction_example ./typeDeduction/TypeDeduction.cpp)
add_executable(explicit_type_deduction_guide ./typeDeduction/explicit_TDguide.cpp)

# SFINAE
add_executable(enable_if ./SFINAE/enable_if.cpp)
add_executable(SFINAE_example1 ./SFINAE/SFINAE.cpp)

add_executable(traits traits.cpp)
# 完美转发
add_executable(perfect_forwarding perfect_forwarding.cpp)