#pragma once

#include <memory>
#include "Window.hpp"
#include "EventManager.hpp"
#include "InfoBox.hpp"

namespace Engine
{
    class LayeredMap;

    struct SharedContext
    {
        SharedContext()
            :m_wind(nullptr)
            ,m_eventManager(nullptr)
            ,m_game_map(nullptr)
        {

        }
            
        std::shared_ptr<Window> m_wind;
        std::shared_ptr<EventManager> m_eventManager;
        std::shared_ptr<LayeredMap> m_game_map;
        std::shared_ptr<InfoBox> m_info_box;
    };
}// namespace Engine

