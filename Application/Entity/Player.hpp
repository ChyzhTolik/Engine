#pragma once

#include "Character.hpp"
#include "EventManager.hpp"

namespace Engine
{
    class Player : public Character
    {
    public:
        Player(EntityManager& l_entityMgr);
        ~Player();
        virtual void OnEntityCollision(EntityBase& l_collider, bool l_attack) override;
        void React(EventDetails& l_details);
    
    private:
        class MoveAction : public ActionFunctinoid
        {
        public:
            MoveAction(Player& l_entity);
            virtual void execute(EventDetails& l_details) override;
        private:
            Player& m_entity;
        };
    };
} // namespace Engine
