#pragma once
#include "Window.hpp"
#include "EventManager.hpp"

namespace Engine
{
    struct SharedContext
    {
        SharedContext(Window& l_window, EventManager& l_event_manager)
            :m_wind(l_window),
            m_eventManager(l_event_manager)
        {

        }
            
        Window& m_wind;
        EventManager& m_eventManager;
    };
}// namespace Engine

