#include "Game.hpp"
#include "StateManager.hpp"
#include <iostream>
#include <memory>

namespace Engine
{
    Game::Game() :
        m_window (std::make_shared<Window>("Engine", sf::Vector2u(800,600))),
        m_state_manager(m_context),
        m_manager(m_context, 100)
    {
        m_clock.restart();
        srand(time(nullptr));
        m_context.m_wind = m_window;
        m_context.m_eventManager = m_window->GetEventManager();

        m_state_manager.SwitchTo(StateType::Intro);
    }

    Game::~Game()
    {

    }

    void Game::update()
    {
        m_window->Update();
        m_state_manager.Update(m_elapsed);
    }

    void Game::render()
    {
        m_window->BeginDraw();
        m_state_manager.Draw();
        m_window->EndDraw();
    }

    sf::Time Game::GetElapsed()
    { 
        return m_elapsed; 
    }

    void Game::RestartClock()
    { 
        m_elapsed += m_clock.restart();

        float frametime = 1.0f / 60.0f;
        if(m_elapsed.asSeconds() >= frametime)
        {
            // Do something 60 times a second.
            
            m_elapsed -= sf::seconds(frametime); // Subtracting.
        }
    }    

    Window& Game::get_window()
    { 
        return *m_window; 
    }

    void Game::run()
    {
        while(!get_window().IsDone())
        {
            update();
            render();
            LateUpdate();
        }
    }

    void Game::handle_input()
    {

    }

    void Game::LateUpdate()
    {
        m_state_manager.ProcessRequests();
        RestartClock();
    }
} // namespace Engine
