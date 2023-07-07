#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
    enum class EntityType{ Base, Enemy, Player };

    enum class EntityState
    {
        Idle, Walking, Jumping, Attacking, Hurt, Dying
    };

    class EntityManager;

    class EntityBase
    {
        friend class EntityManager;
        EntityBase(EntityManager* l_entityMgr);
        virtual ~EntityBase();
        // Getters and setters.
        void Move(float l_x, float l_y);
        void AddVelocity(float l_x, float l_y);
        void Accelerate(float l_x, float l_y);
        void SetAcceleration(float l_x, float l_y);
        void ApplyFriction(float l_x, float l_y);
        virtual void Update(float l_dT);
        virtual void Draw(sf::RenderWindow& l_wind) = 0;
        protected:
        // Methods.
        void UpdateAABB();
        void CheckCollisions();
        void ResolveCollisions();
        // Method for what THIS entity does TO the l_collider entity.
        virtual void OnEntityCollision(EntityBase* l_collider,
        bool l_attack) = 0;
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
        TileInfo* m_referenceTile; // Tile underneath entity.
        sf::Vector2f m_size; // Size of the collision box.
        sf::FloatRect m_AABB; // The bounding box for collisions.
        EntityState m_state; // Current entity state.
        // Flags for remembering axis collisions.
        bool m_collidingOnX;
        bool m_collidingOnY;
        Collisions m_collisions;
        EntityManager* m_entityManager;
    };
    
} // namespace Engine
