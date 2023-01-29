cmake_minimum_required(VERSION 3.10)

project(moss)

set(SOURCE_DIR construct-functions/static-member-function)

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)