#pragma once

#include "System.hpp"
#include <memory>
#include "PositionComponent.hpp"
#include "MovableComponent.hpp"

namespace Engine
{
    enum class Axis
    {
        x,
        y
    };

    class LayeredMap;

    class MovementSystem : public System, public std::enable_shared_from_this<MovementSystem>
    {
    public:
        MovementSystem(std::shared_ptr<SystemManager> system_manager);
        ~MovementSystem();

        void set_map(std::shared_ptr<LayeredMap> map);
        void subscribe();

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
    private:
        void movement_step(float time, std::shared_ptr<MovableComponent> movable, std::shared_ptr<PositionComponent> position);
        void stop_entity(EntityId entity, Axis axis);
        void set_direction(EntityId entity, Direction direction);
        const sf::Vector2f get_tile_friction(u_int32_t elevation, int x, int y);

        std::shared_ptr<LayeredMap> m_map;
    };
    
    
    
} // namespace Engine
