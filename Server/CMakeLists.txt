cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(Server)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})