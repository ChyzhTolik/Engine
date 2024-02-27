cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)

project(Common)

set(HEADERS 
    Configuration/Configuration.hpp
    Configuration/ResourceManager.hpp
    Window/Window.hpp
    Window/EventDetails.hpp
    Window/EventManager.hpp
    StateManager/StateManager.hpp
    StateManager/States/State_Game.hpp
    StateManager/States/BaseState.hpp
    StateManager/States/State_Paused.hpp
    StateManager/States/State_Intro.hpp
    StateManager/States/State_MainMenu.hpp

    CommonHeaders/ActionFunctinoid.hpp
    CommonHeaders/Vector2i_hash.hpp
    CommonHeaders/SharedContext.hpp
    CommonHeaders/MapStructs.hpp

    Map/IsoTiles.hpp
    Map/KnightTiles.hpp
    Map/TileTemplate.hpp
    Map/TileSetTemplate.hpp
    Map/TileSetInterface.hpp
    Map/MapLayerInterface.hpp
    Map/MapLayerTemplate.hpp
    Map/MapLayerInterface.hpp
    Map/LayeredMap.hpp
    Map/MapLayerFactory.hpp
)
set(SOURCES 
    Configuration/Configuration.cpp
    Window/Window.cpp
    Window/EventManager.cpp
    StateManager/States/BaseState.cpp
    StateManager/States/State_Paused.cpp
    StateManager/States/State_Game.cpp
    StateManager/States/State_Intro.cpp
    StateManager/States/State_MainMenu.cpp
    StateManager/StateManager.cpp
    Map/LayeredMap.cpp
    Map/MapLayerFactory.cpp
)
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

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
target_include_directories(${PROJECT_NAME} PUBLIC Configuration)
target_include_directories(${PROJECT_NAME} PUBLIC Window)
target_include_directories(${PROJECT_NAME} PUBLIC StateManager)
target_include_directories(${PROJECT_NAME} PUBLIC CommonHeaders)
target_include_directories(${PROJECT_NAME} PUBLIC Map)