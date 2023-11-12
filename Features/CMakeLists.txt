cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
project(test-CppFeatures)

add_executable(variant variant/variant.cpp)
add_executable(tuple tuple/tuple.cpp)
add_executable(optional optional/optional.cpp)
add_executable(myany ./any/main.cpp)
add_executable(myfunction ./function/main.cpp)
add_executable(lambda ./lambda/main.cpp)

# -- other
add_executable(explicit other/explicit.cpp)
add_executable(ifexpr other/Init_statement_for_if.cpp)
add_executable(StructuredBinding other/StructuredBinding.cpp)
add_executable(if_constexpr other/if_constexpr.cpp)
target_compile_options(if_constexpr PRIVATE "-std=c++17")

