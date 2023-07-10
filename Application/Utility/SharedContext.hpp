#pragma once
#include "Window.hpp"
#include "EventManager.hpp"
#include "EntityManager.hpp"

namespace Engine
{
    class TileMap;

    struct SharedContext
    {
        SharedContext(Window& l_window, EventManager& l_event_manager, EntityManager& l_entity_manager, TileMap& l_tile_map)
            :m_wind(l_window),
            m_eventManager(l_event_manager),
            m_entityManager(l_entity_manager),
            m_gameMap(l_tile_map)
        {

        }
            
        Window& m_wind;
        EventManager& m_eventManager;
        EntityManager& m_entityManager;
        TileMap& m_gameMap;
    };
}// namespace Engine

