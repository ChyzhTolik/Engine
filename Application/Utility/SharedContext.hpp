#pragma once

#include <memory>
#include "Window.hpp"
#include "EventManager.hpp"
#include "EntityManager.hpp"
#include "EntitiesManager.hpp"
#include "SystemManager.hpp"

namespace Engine
{
    class TileMap;

    struct SharedContext
    {
        SharedContext()
            :m_wind(nullptr),
            m_eventManager(nullptr),
            m_entityManager(nullptr),
            m_gameMap(nullptr),
            m_entities_manager(nullptr),
            m_system_manager(nullptr)
        {

        }
            
        std::shared_ptr<Window> m_wind;
        std::shared_ptr<EventManager> m_eventManager;
        std::shared_ptr<EntityManager> m_entityManager;
        std::shared_ptr<TileMap> m_gameMap;
        std::shared_ptr<EntitiesManager> m_entities_manager;
        std::shared_ptr<SystemManager> m_system_manager;
    };
}// namespace Engine

