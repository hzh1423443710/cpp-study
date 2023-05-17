cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(LearnCpp)

add_subdirectory("./0test")

# add_compile_options(-fno-elide-constructors)  
set(PROJECT_SOURCES "./smart_ptr/main.cpp")

add_executable("LearnCpp" ${PROJECT_SOURCES})