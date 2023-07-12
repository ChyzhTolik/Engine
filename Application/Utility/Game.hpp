#pragma once

#include "Window.hpp"
#include "ActionFunctinoid.hpp"
#include "StateManager.hpp"
#include "SharedContext.hpp"
#include "EntityManager.hpp"

namespace Engine
{
    class Game
    {
    private:
        std::shared_ptr<Window> m_window;
        sf::Clock m_clock;
	    sf::Time m_elapsed;
        StateManager m_state_manager;
        SharedContext m_context;
        std::shared_ptr<EntityManager> m_manager;

    public:
        Game();
        ~Game();
        Window& get_window();
        void run();
        sf::Time GetElapsed();
	    void RestartClock();
        void LateUpdate();

    private:
        void handle_input();
        void update();
        void render();
    };    
} // namespace Engine

