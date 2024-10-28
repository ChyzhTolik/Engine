cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(TestApp)

set(SOURCES 
    main.cpp 
    testing_libs.cpp
    TestClasses/Hero.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

set (SPDLOG ${CMAKE_SOURCE_DIR}/external/spdlog/include)

target_link_libraries(${PROJECT_NAME} Common)
target_link_libraries(${PROJECT_NAME} Game)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog_header_only)

target_include_directories(${PROJECT_NAME} PUBLIC ${SPDLOG})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Common)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Game)

file(COPY ${CMAKE_SOURCE_DIR}/media DESTINATION ${CMAKE_BINARY_DIR}/TestApp/)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/media
    ${CMAKE_BINARY_DIR}/TestApp/media
)