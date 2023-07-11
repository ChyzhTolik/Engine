#pragma once

#include <memory>
#include "Window.hpp"
#include "EventManager.hpp"
#include "EntityManager.hpp"

namespace Engine
{
    class TileMap;

    struct SharedContext
    {
        SharedContext()
            :m_wind(nullptr),
            m_eventManager(nullptr),
            m_entityManager(nullptr),
            m_gameMap(nullptr)
        {

        }
            
        std::shared_ptr<Window> m_wind;
        std::shared_ptr<EventManager> m_eventManager;
        std::shared_ptr<EntityManager> m_entityManager;
        std::shared_ptr<TileMap> m_gameMap;
    };
}// namespace Engine

