cmake_minimum_required(VERSION 3.26.0)

set(CMAKE_CXX_STANDARD 17)

project(Tests)

set(SOURCES 
    ConfigurationTests.cpp
    StateManagerTests/StateManagerTests.cpp
    MapTests/MapTests.cpp
    AnimationsTests/AnimationsTests.cpp
    EntitiesTests/EntitiesTests.cpp
    ComponentsTests/ComponentsTests.cpp
    SystemsTests/SystemManagerTests.cpp
    SystemsTests/RendererSystemTests.cpp
    SystemsTests/MovementSystemTests.cpp
    SystemsTests/StateSystemTests.cpp
    SystemsTests/ControllerSystemTests.cpp
    SystemsTests/SpriteSheetSystemTests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC Common)
target_link_libraries(${PROJECT_NAME} PUBLIC gtest_main)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Common)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

file(COPY ${CMAKE_SOURCE_DIR}/media DESTINATION ${CMAKE_BINARY_DIR}/Tests/)
file(COPY ${CMAKE_SOURCE_DIR}/media DESTINATION ${CMAKE_BINARY_DIR}/)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/media
    ${CMAKE_BINARY_DIR}/media
)