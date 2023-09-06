cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)

project(Engine)

set (SOURCES_FILES
    main.cpp
    Test/testing.cpp
    Test/Engine_classes.hpp
    Action/Action.cpp
    Configuration/Configuration.cpp
    MainWindow.cpp
    TestPlayer.cpp
    Animations/Animation.cpp
    Animations/AnimatedSprite.cpp
    Utility/Window.cpp
    Utility/Game.cpp
    Utility/EventManager.cpp
    Utility/StateManager.cpp
    Utility/State_Intro.cpp
    Utility/BaseState.cpp
    Utility/State_MainMenu.cpp
    Utility/State_Game.cpp
    Utility/State_Paused.cpp
    Utility/Map/Background.cpp
    Utility/Map/Tile.cpp
    Utility/Map/TileSet.cpp
    Utility/Map/TileMap.cpp
    Animations/Anim_Base.cpp
    Animations/SpriteSheet.cpp
    Animations/Anim_Directional.cpp
    Animations/Direction.hpp
    Entity/EntityBase.cpp
    Entity/EntityManager.cpp
    Entity/Character.cpp
    Entity/Player.cpp
    Entity/Enemy.cpp
    Components/Component.cpp
    Components/PositionComp.cpp
    Components/EntitiesManager.cpp
    Components/System.cpp
    Components/MessageHandler.cpp
    Components/EntityMessages.hpp
    Components/SystemManager.cpp
    Components/EventQueue.hpp
    Components/DrawableComponent.cpp
    Components/SpriteSheetComponent.cpp
    Components/RendererSystem.cpp
    Components/MovableComponent.cpp
    Components/MovementSystem.cpp
    Components/StateComponent.cpp
    Components/StateSystem.cpp
    Components/ControllerComponent.cpp
    Components/ControllerSystem.cpp
    Components/AnimationSystem.cpp
    Components/CollisionComponent.cpp
    Components/CollisionSystem.cpp
    Components/ComponentCreator.cpp
    NewMap/Tile.cpp
    NewMap/KnightTiles.hpp
    NewMap/IsoTiles.hpp
    NewMap/TileSet.cpp
    NewMap/LayeredMap.cpp
    Common/Vector2i_hash.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES_FILES})

set (INCLUDES ${CMAKE_SOURCE_DIR}/external/include)

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
    
if(WIN32)
    set(WINDOWS_LIBS ${CMAKE_SOURCE_DIR}/external/Windows)
    target_link_libraries(${PROJECT_NAME} 
        ${WINDOWS_LIBS}/sfml-audio-d.lib
        ${WINDOWS_LIBS}/sfml-window-d.lib
        ${WINDOWS_LIBS}/sfml-system-d.lib
        ${WINDOWS_LIBS}/sfml-graphics-d.lib

        ${WINDOWS_LIBS}/SFGUI-d.lib

        ${WINDOWS_LIBS}/box2d.lib
    )

    add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${WINDOWS_LIBS}/sfml-audio-d-3.dll
            ${WINDOWS_LIBS}/sfml-graphics-d-3.dll
            ${WINDOWS_LIBS}/sfml-network-d-3.dll
            ${WINDOWS_LIBS}/sfml-system-d-3.dll
            ${WINDOWS_LIBS}/sfml-window-d-3.dll
            ${WINDOWS_LIBS}/openal32.dll

            ${WINDOWS_LIBS}/box2d.dll

            ${WINDOWS_LIBS}/SFGUI-d.dll

            ${CMAKE_BINARY_DIR}/Application
    )
endif(WIN32)

target_include_directories(${PROJECT_NAME} PRIVATE Animations)
target_include_directories(${PROJECT_NAME} PRIVATE Test)
target_include_directories(${PROJECT_NAME} PRIVATE Action)
target_include_directories(${PROJECT_NAME} PRIVATE Configuration)
target_include_directories(${PROJECT_NAME} PRIVATE Utility)
target_include_directories(${PROJECT_NAME} PRIVATE Utility/Map)
target_include_directories(${PROJECT_NAME} PRIVATE Entity)
target_include_directories(${PROJECT_NAME} PRIVATE Components)
target_include_directories(${PROJECT_NAME} PRIVATE NewMap)
target_include_directories(${PROJECT_NAME} PRIVATE Common)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

file(COPY ${CMAKE_SOURCE_DIR}/Application/media DESTINATION ${CMAKE_BINARY_DIR}/Application/)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Application/media
    ${CMAKE_BINARY_DIR}/Application/media
)