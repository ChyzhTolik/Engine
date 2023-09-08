#pragma once

#include "System.hpp"
#include "Direction.hpp"
#include <SFML/System.hpp>
#include "MovableComponent.hpp"
#include "PositionComp.hpp"

namespace Engine
{
    class TileMap;

    enum class Axis
    {
        x,
        y,
    };

    class MovementSystem : public System, public std::enable_shared_from_this<MovementSystem>
    {
    public:
        MovementSystem(std::shared_ptr<SystemManager> l_system_manager);
        ~MovementSystem();
        void Update(float l_dT) override;
        void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
        void Notify(const Message& l_message) override;
        void SetMap(std::shared_ptr<TileMap> l_gameMap);
    private:
        void StopEntity(const EntityId& l_entity, const Axis& l_axis);
        void SetDirection(const EntityId& l_entity, const Direction& l_dir);
        const sf::Vector2f& GetTileFriction(uint32_t l_elevation, uint32_t l_x, uint32_t l_y);
        void MovementStep(float l_dT, std::shared_ptr<MovableComponent> l_movable, std::shared_ptr<PositionComp> l_position);
        std::shared_ptr<TileMap> m_gameMap;
    };
} // namespace Engine
