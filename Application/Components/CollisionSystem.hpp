#pragma once

#include "System.hpp"
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "PositionComp.hpp"
#include "CollisionComponent.hpp"
#include "EntityBase.hpp"

namespace Engine
{
    class CollisionSystem : public System
    {
    public:
        CollisionSystem(std::shared_ptr<SystemManager> l_system_manager);
        ~CollisionSystem();
        void Update(float l_dT) override;
        void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
        void Notify(const Message& l_message) override;
        void SetMap(std::shared_ptr<TileMap> l_map);
    private:
        void CheckOutOfBounds(std::shared_ptr<PositionComp> l_pos, std::shared_ptr<CollisionComponent> l_col);
        void MapCollisions(const EntityId& l_entity, std::shared_ptr<PositionComp> l_pos, std::shared_ptr<CollisionComponent> l_col);
        void EntityCollisions();
        std::shared_ptr<TileMap> m_gameMap;
    };
    
    
    
} // namespace Engine
