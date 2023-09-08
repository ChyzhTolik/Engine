#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <Tile.hpp>
#include "Direction.hpp"

namespace Engine
{
    enum class EntityType{ Base, Enemy, Player };

    enum class EntityState
    {
        Idle, Walking, Jumping, Attacking, Hurt, Dying
    };

    struct CollisionElement
    {
        CollisionElement(float l_area, std::shared_ptr<TileInfo> l_info,  const sf::FloatRect& l_bounds):
            m_area(l_area),
            m_tile(l_info), 
            m_tileBounds(l_bounds)
        {

        }

        float m_area;
        std::shared_ptr<TileInfo> m_tile;
        sf::FloatRect m_tileBounds;
    };

    using Collisions = std::vector<CollisionElement>;

    bool SortCollisions(const CollisionElement& l_1,const CollisionElement& l_2);

    class EntityManager;

    class EntityBase
    {
    public:
        friend class EntityManager;
        EntityBase(EntityManager& l_entityMgr);
        virtual ~EntityBase();
        void SetPosition(const float& l_x, const float& l_y);
        void SetPosition(const sf::Vector2f& l_pos);
        void SetSize(const float& l_x, const float& l_y);
        void SetState(const EntityState& l_state);

        const sf::Vector2f& GetPosition()const;
        const sf::Vector2f& GetSize()const;
        EntityState GetState()const;
        std::string GetName()const;
        unsigned int GetId()const;
        EntityType GetType()const;

        void Move(float l_x, float l_y);
        void AddVelocity(float l_x, float l_y);
        void Accelerate(float l_x, float l_y);
        void SetAcceleration(float l_x, float l_y);
        void ApplyFriction(float l_x, float l_y);
        virtual void Update(float l_dT);
        virtual void Draw(sf::RenderWindow& l_wind) = 0;

    protected:
        // Methods.
        virtual void UpdateAABB(Direction direction = Direction::Right);
        void CheckCollisions();
        void ResolveCollisions();
        // Method for what THIS entity does TO the l_collider entity.
        virtual void OnEntityCollision(EntityBase& l_collider, bool l_attack) = 0;
        // Data members.
        std::string m_name;
        EntityType m_type;
        unsigned int m_id; // Entity id in the entity manager.
        sf::Vector2f m_position; // Current position.
        sf::Vector2f m_positionOld; // Position before entity moved.
        sf::Vector2f m_velocity; // Current velocity.
        sf::Vector2f m_maxVelocity; // Maximum velocity.
        sf::Vector2f m_speed; // Value of acceleration.
        sf::Vector2f m_acceleration; // Current acceleration.
        sf::Vector2f m_friction; // Default friction value.
        std::shared_ptr<TileInfo> m_referenceTile; // Tile underneath entity.
        sf::Vector2f m_size; // Size of the collision box.
        sf::Rect<float> m_AABB; // The bounding box for collisions.
        EntityState m_state; // Current entity state.
        // Flags for remembering axis collisions.
        bool m_collidingOnX;
        bool m_collidingOnY;
        Collisions m_collisions;
        EntityManager& m_entityManager;
        Direction m_direction;
    };
    
} // namespace Engine
