cmake_minimum_required(VERSION 4.0)

project(PRINT)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes/ utils/)

set(SOURCE
    src/Task1.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})
