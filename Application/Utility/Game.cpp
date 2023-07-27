#include "Game.hpp"
#include "StateManager.hpp"
#include <iostream>
#include <memory>

namespace Engine
{
    Game::Game() :
        m_window (std::make_shared<Window>("Engine", sf::Vector2u(800,600))),
        m_state_manager(m_context),
        m_manager(std::make_shared<EntityManager>(m_context, 100)),
        m_system_manager(std::make_shared<SystemManager>()),
        m_entities_manager(std::make_shared<EntitiesManager>(m_system_manager))
    {
        m_clock.restart();
        srand(time(nullptr));
        m_context.m_wind = m_window;
        m_context.m_eventManager = m_window->GetEventManager();
        m_context.m_entityManager = m_manager;

        m_state_manager.SwitchTo(StateType::Intro);
        m_system_manager->SetEntityManager(m_entities_manager);

        m_context.m_entities_manager = m_entities_manager;
        m_context.m_system_manager = m_system_manager;
    }

    Game::~Game()
    {

    }

    void Game::update()
    {
        m_window->Update();

        m_repaint = false;
		m_elapsed += m_clock.restart();

        while (m_elapsed > m_time_per_frame)
        {
            m_elapsed -= m_time_per_frame;
            m_repaint = true;

            m_state_manager.Update(m_time_per_frame);
        }
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

    void Game::run(uint32_t frames_per_second)
    {
        m_time_per_frame = sf::seconds(1.f/frames_per_second);

        while(!get_window().IsDone())
        {
            update();

            if (m_repaint)
            {
                render();
            }
            
            LateUpdate();
        }
    }

    void Game::handle_input()
    {

    }

    void Game::LateUpdate()
    {
        m_state_manager.ProcessRequests();
        // RestartClock();
    }
} // namespace Engine
