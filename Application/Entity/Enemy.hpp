#pragma once
#include "Character.hpp"

namespace Engine
{
    class Enemy : public Character
    {
    public:
        Enemy(EntityManager& l_entityMgr);
        ~Enemy();
        virtual void OnEntityCollision(EntityBase& l_collider, bool l_attack) override;
        void Update(float l_dT);
    private:
        sf::Vector2f m_destination;
        bool m_hasDestination;
    };
    
} // namespace Engine
