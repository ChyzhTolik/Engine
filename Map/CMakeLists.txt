cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)

project(Map)

set(HEADERS 
    IsoTiles.hpp
    KnightTiles.hpp
    LayeredMap.hpp
    Tile.hpp
    TileSet.hpp
)
set(SOURCES 
    LayeredMap.cpp
    Tile.cpp
    TileSet.cpp
)
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC Common) 

set (INCLUDES ${CMAKE_SOURCE_DIR}/external/include)
if(UNIX)
    set(UNIX_LIBS ${CMAKE_SOURCE_DIR}/external/UNIX)
    target_link_libraries(${PROJECT_NAME} 
        PUBLIC ${UNIX_LIBS}/libsfml-audio-d.so.3.0.0
        PUBLIC ${UNIX_LIBS}/libsfml-window-d.so.3.0.0
        PUBLIC ${UNIX_LIBS}/libsfml-system-d.so.3.0.0
        PUBLIC ${UNIX_LIBS}/libsfml-graphics-d.so.3.0.0

        PUBLIC ${UNIX_LIBS}/libSFGUI-d.so

        PUBLIC ${UNIX_LIBS}/libbox2d.so.2.4.1
    )
endif(UNIX)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Common)

