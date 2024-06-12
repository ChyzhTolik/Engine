#pragma once

#include <memory>
#include "Window.hpp"
#include "EventManager.hpp"
#include "InfoBox.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"

namespace Engine
{
    class LayeredMap;

    struct SharedContext
    {
        SharedContext()
            :m_wind(nullptr)
            ,m_eventManager(nullptr)
            ,m_game_map(nullptr)
            ,m_system_manager(nullptr)
            ,m_entities_manager(nullptr)
        {

        }
            
        std::shared_ptr<Window> m_wind;
        std::shared_ptr<EventManager> m_eventManager;
        std::shared_ptr<LayeredMap> m_game_map;
        std::shared_ptr<InfoBox> m_info_box;
        std::shared_ptr<SystemManager> m_system_manager;
        std::shared_ptr<EntitiesManager> m_entities_manager;
    };
}// namespace Engine

