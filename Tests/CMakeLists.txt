cmake_minimum_required(VERSION 3.26.0)

set(CMAKE_CXX_STANDARD 17)

project(Tests)

set(SOURCES 
    ConfigurationTests.cpp
    StateManagerTests/StateManagerTests.cpp
    MapTests/MapTests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC Common)
target_link_libraries(${PROJECT_NAME} PUBLIC gtest_main)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Common)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Application/media
    ${CMAKE_BINARY_DIR}/media
)