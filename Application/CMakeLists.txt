cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)

project(Engine)

set (SOURCES_FILES
    main.cpp
    Test/testing.cpp
    Action/Action.cpp
    Configuration/Configuration.cpp
    MainWindow.cpp
    TestPlayer.cpp
    Animations/Animation.cpp
    Animations/AnimatedSprite.cpp
    Utility/Window.cpp
    Utility/Game.cpp
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

target_include_directories(${PROJECT_NAME} PRIVATE Test)
target_include_directories(${PROJECT_NAME} PRIVATE Action)
target_include_directories(${PROJECT_NAME} PRIVATE Configuration)
target_include_directories(${PROJECT_NAME} PRIVATE Animations)
target_include_directories(${PROJECT_NAME} PRIVATE Utility)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

