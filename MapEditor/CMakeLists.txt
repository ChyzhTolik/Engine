cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(MapEditor)

set(SOURCES 
    main.cpp 
    FileReader.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

set (INCLUDES ${CMAKE_SOURCE_DIR}/external/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Common/Map)

file(COPY ${CMAKE_SOURCE_DIR}/MapEditor/InputFiles DESTINATION ${CMAKE_BINARY_DIR}/MapEditor)