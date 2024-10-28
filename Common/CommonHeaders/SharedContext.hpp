#pragma once

#include <memory>
#include "Window.hpp"
#include "EventManager.hpp"
#include "InfoBox.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"

#include "spdlog/spdlog.h"

namespace Engine
{
    class LayeredMap;

    struct SharedContext
    {
        SharedContext();
            
        std::shared_ptr<Window> m_wind;
        std::shared_ptr<EventManager> m_eventManager;
        std::shared_ptr<LayeredMap> m_game_map;
        std::shared_ptr<InfoBox> m_info_box;
        std::shared_ptr<SystemManager> m_system_manager;
        std::shared_ptr<EntitiesManager> m_entities_manager;
        std::shared_ptr<spdlog::logger> m_log_file;
    };
}// namespace Engine

