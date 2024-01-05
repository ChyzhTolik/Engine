cmake_minimum_required(VERSION 3.18.0)
set(CMAKE_CXX_STANDARD 17)

project(Tests)

set(SOURCES ConfigurationTests.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest_main Common)
if(UNIX)
set(UNIX_LIBS ${CMAKE_SOURCE_DIR}/external/UNIX)
target_link_libraries(${PROJECT_NAME} 
${UNIX_LIBS}/libsfml-audio-d.so.3.0.0
${UNIX_LIBS}/libsfml-window-d.so.3.0.0
${UNIX_LIBS}/libsfml-system-d.so.3.0.0
${UNIX_LIBS}/libsfml-graphics-d.so.3.0.0

${UNIX_LIBS}/libSFGUI-d.so

${UNIX_LIBS}/libbox2d.so.2.4.1
)
endif(UNIX)

set (INCLUDES ${CMAKE_SOURCE_DIR}/external/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Common)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
