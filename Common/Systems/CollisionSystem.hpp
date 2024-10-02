#pragma once

#include "System.hpp"
#include <vector>
#include "LayeredMap.hpp"
#include "PositionComponent.hpp"
#include "CollidableComponent.hpp"
#include "Tile.hpp"

namespace Engine
{
    struct CollisionInfo
    {
        float area;
        std::shared_ptr<Tile> tile_info;
        sf::FloatRect tile_bounds;
    };

    class CollisionSystem : public System
    {
    public:
        CollisionSystem(std::shared_ptr<SystemManager> system_manager);
        ~CollisionSystem();

        void set_map(std::shared_ptr<LayeredMap> map);

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
    private:
        void check_out_of_bounds(std::shared_ptr<PositionComponent> position, std::shared_ptr<CollidableComponent> collidable);
        void map_collisions(EntityId entity, 
            std::shared_ptr<PositionComponent> position, 
            std::shared_ptr<CollidableComponent> collidable);
        void entity_collisions();

        std::shared_ptr<LayeredMap> m_map;
    };
} // namespace Engine
