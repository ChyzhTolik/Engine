cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)

project(Game)

set(HEADERS
    Game.hpp
)
set(SOURCES
    Game.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Common)

set (INCLUDES ${CMAKE_SOURCE_DIR}/external/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Common)
