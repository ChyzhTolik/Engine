#include "StateSystem.hpp"

#include "Component.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "Direction.hpp"

namespace Engine
{
    StateSystem::StateSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::State, l_system_manager)
    {
        std::bitset<REQUIREMENTS_NUM> req;
        req.set((unsigned int)ComponentType::State);
        m_requiredComponents.push_back(req);
        m_system_manager->GetMessageHandler().Subscribe(EntityMessage::Move,shared_from_this());
        m_system_manager->GetMessageHandler().Subscribe(EntityMessage::Switch_State,shared_from_this());
    }
    
    StateSystem::~StateSystem()
    {
    }

    void StateSystem::Update(float l_dT)
    {
        auto entities = m_system_manager->GetEntityManager();

        for(auto &entity : m_entities)
        {
            auto state = entities->GetComponent<StateComponent>(entity, ComponentType::State);

            if(state->GetState() == EntityState::Walking)
            {
                Message msg((MessageType)EntityMessage::Is_Moving);
                msg.m_receiver = entity;
                m_system_manager->GetMessageHandler().Dispatch(msg);
            }
        }
    }

    void StateSystem::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event)
    {
        switch(l_event)
        {
            case EntityEvent::Became_Idle:
            ChangeState(l_entity,EntityState::Idle,false);
            break;
        }
    }

    void StateSystem::ChangeState(const EntityId& l_entity, const EntityState& l_state, const bool& l_force)
    {
        auto entities = m_system_manager->GetEntityManager();
        auto state = entities->GetComponent<StateComponent>(l_entity, ComponentType::State);

        if (!l_force && state->GetState() == EntityState::Dying)
        {
            return;
        }

        state->SetState(l_state);
        Message msg((MessageType)EntityMessage::State_Changed);
        msg.m_receiver = l_entity;
        msg.m_info = (int)l_state;
        m_system_manager->GetMessageHandler().Dispatch(msg);
    }

    void StateSystem::Notify(const Message& l_message)
    {
        if (!HasEntity(l_message.m_receiver))
        { 
            return; 
        }

        EntityMessage m = (EntityMessage)l_message.m_type;
        switch(m)
        {
            case EntityMessage::Move:
            {
                auto state = m_system_manager->GetEntityManager()->GetComponent<StateComponent>(l_message.m_receiver,ComponentType::State);

                if (state->GetState() == EntityState::Dying)
                { 
                    return; 
                }

                EntityEvent e;

                if (std::get<int>(l_message.m_info) == static_cast<int>(Direction::Up))
                {
                    e = EntityEvent::Moving_Up;
                } 
                else if (std::get<int>(l_message.m_info) == static_cast<int>(Direction::Down))
                {
                    e = EntityEvent::Moving_Down;
                } 
                else if(std::get<int>(l_message.m_info) == static_cast<int>(Direction::Left))
                {
                    e = EntityEvent::Moving_Left;
                } 
                else if (std::get<int>(l_message.m_info) == static_cast<int>(Direction::Right))
                {
                    e = EntityEvent::Moving_Right;
                }

                m_system_manager->AddEvent(l_message.m_receiver, (EventID)e);
                ChangeState(l_message.m_receiver, EntityState::Walking,false);
            }
            break;

            case EntityMessage::Switch_State:
            ChangeState(l_message.m_receiver,(EntityState)std::get<int>(l_message.m_info),false);
            break;
        }
    }
} // namespace Engine
