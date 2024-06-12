#pragma once

#include "Window.hpp"
#include "ActionFunctinoid.hpp"
#include "StateManager.hpp"
#include "SharedContext.hpp"

namespace Engine
{
    class Game
    {
    public:
        Game();
        ~Game();
        Window& get_window();
        void run(uint32_t frames_per_second);
        sf::Time GetElapsed();

    private:
	    void RestartClock();
        void LateUpdate();
        void handle_input();
        void update();
        void render();

    private:
        std::shared_ptr<Window> m_window;
        sf::Clock m_clock;
	    sf::Time m_elapsed;
        sf::Time m_time_per_frame;
        bool m_repaint = false;
        StateManager m_state_manager;
        SharedContext m_context;
        
    };    
} // namespace Engine

