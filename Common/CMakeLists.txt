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
    CommonHeaders/Direction.hpp

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
    Map/Tile.hpp

    Animations/SpriteSheet.hpp
    Animations/Anim_Base.hpp
    Animations/AnimatedSprite.hpp
    Animations/Animation.hpp
    Animations/Anim_Directional.hpp
    Animations/SpriteSheetTemplate.hpp
    Animations/AnimationTypes.hpp

    Entities/Character.hpp 
    Entities/Enemy.hpp 
    Entities/EntityBase.hpp 
    Entities/EntityManager.hpp 
    Entities/Player.hpp
    Entities/EntityActions.hpp
    InfoBox/InfoBox.hpp

    Components/Component.hpp
    Components/PositionComponent.hpp
    Components/MovableComponent.hpp
    Components/StateComponent.hpp
    Components/ControllerComponent.hpp
    Components/SpriteSheetComponent.hpp
    Components/CollidableComponent.hpp

    EntitiesManager/EntitiesManager.hpp

    Systems/SystemManager.hpp
    Systems/EventQueue.hpp
    Systems/System.hpp
    Systems/Observer.hpp
    Systems/Message.hpp
    Systems/Communicator.hpp
    Systems/MessageHandler.hpp
    Systems/EntityMessage.hpp
    Systems/EntityEvent.hpp

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

    Animations/SpriteSheet.cpp
    Animations/Anim_Base.cpp
    Animations/AnimatedSprite.cpp
    Animations/Animation.cpp
    Animations/Anim_Directional.cpp

    Entities/Character.cpp 
    Entities/Enemy.cpp 
    Entities/EntityBase.cpp 
    Entities/EntityManager.cpp 
    Entities/Player.cpp
    Entities/EntityActions.cpp
    InfoBox/InfoBox.cpp

    Components/Component.cpp
    Components/PositionComponent.cpp
    Components/MovableComponent.cpp
    Components/StateComponent.cpp
    Components/ControllerComponent.cpp
    Components/SpriteSheetComponent.cpp
    Components/CollidableComponent.cpp

    Systems/SystemManager.cpp
    Systems/EventQueue.cpp
    Systems/System.cpp
    Systems/Communicator.cpp
    Systems/MessageHandler.cpp


    EntitiesManager/EntitiesManager.cpp
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
target_include_directories(${PROJECT_NAME} PUBLIC Animations)
target_include_directories(${PROJECT_NAME} PUBLIC InfoBox)
target_include_directories(${PROJECT_NAME} PUBLIC Components)
target_include_directories(${PROJECT_NAME} PUBLIC EntitiesManager)
target_include_directories(${PROJECT_NAME} PUBLIC Systems)