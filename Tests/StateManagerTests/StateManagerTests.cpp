#include <gtest/gtest.h>

#include <StateManager/StateManager.hpp>
#include <Configuration/Configuration.hpp>

TEST(StateManagerTest, TestHasStates)
{
    Engine::Configuration::Initialize();
    std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Engine", sf::Vector2u(800,600));
    Engine::SharedContext context;
    context.m_wind = window;
    context.m_eventManager = context.m_wind->GetEventManager();

    Engine::StateManager state_manager(context);
    state_manager.SwitchTo(Engine::StateType::Intro);
    EXPECT_EQ(state_manager.HasState(Engine::StateType::Intro), true);

    // const auto& state = state_manager.get_state(Engine::StateType::Intro);

    Engine::EventDetails details("Intro_Continue");   
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    context.m_eventManager->execute_action(Engine::StateType::Intro, "Intro_Continue", details);

    EXPECT_EQ(state_manager.HasState(Engine::StateType::MainMenu), true);

    details.m_mouse.x = 300;
    details.m_mouse.y = 200;
    context.m_eventManager->execute_action(Engine::StateType::MainMenu, "Mouse_Left", details);
    EXPECT_EQ(state_manager.HasState(Engine::StateType::Game), true);

    context.m_eventManager->execute_action(Engine::StateType::Game, "Key_P", details);
    EXPECT_EQ(state_manager.HasState(Engine::StateType::Paused), true);

    context.m_eventManager->execute_action(Engine::StateType::Paused, "Key_P", details);
    EXPECT_EQ(state_manager.HasState(Engine::StateType::Game), true);
}