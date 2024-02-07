cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(TestApp)

set(SOURCES main.cpp testing_libs.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Common)
target_link_libraries(${PROJECT_NAME} Game)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Common)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Game)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Application/media
    ${CMAKE_BINARY_DIR}/TestApp/media
)