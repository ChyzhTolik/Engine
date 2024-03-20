#pragma once

#include "Character.hpp"
#include "EventManager.hpp"

namespace Engine
{
    class PlayerCreator : public EntityCreator
    {
    public: 
        PlayerCreator(EntityManager& l_entity_manager);
        virtual std::shared_ptr<EntityBase> create() override;    
    };

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

        class JumpAction : public ActionFunctinoid
        {
        public:
            JumpAction(Player& l_entity);
            virtual void execute(EventDetails& l_details) override;
        private:
            Player& m_entity;
        };

        class AttackAction : public ActionFunctinoid
        {
        public:
            AttackAction(Player& l_entity);
            virtual void execute(EventDetails& l_details) override;
        private:
            Player& m_entity;
        };
    };
} // namespace Engine
