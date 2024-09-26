#include "StateSystem.hpp"

#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "StateComponent.hpp"

namespace Engine
{
    StateSystem::StateSystem(std::shared_ptr<SystemManager> system_manager) : System(SystemType::State, system_manager)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::State));

        m_required_components.push_back(mask);
    }
    
    void StateSystem::subscribe()
    {
        m_system_manager->get_message_handler()->subscribe(EntityMessage::Move, shared_from_this());
        m_system_manager->get_message_handler()->subscribe(EntityMessage::Switch_State, shared_from_this());
        m_system_manager->get_message_handler()->subscribe(EntityMessage::Jump, shared_from_this());
    }

    StateSystem::~StateSystem()
    {

    }

    void StateSystem::update(float time)
    {
        auto entity_manager = m_system_manager->get_entity_manager();

        for (auto&& entity : m_entities)
        {
            auto state_component = entity_manager->get_component<StateComponent>(entity, ComponentType::State);

            if (state_component->get_state() == EntityState::Walking)
            {
                Message message(EntityMessage::Is_Moving);
                message.m_receiver = entity;
                m_system_manager->get_message_handler()->dispatch(message);
            }

            if (state_component->get_state() == EntityState::Jumping)
            {
                Message message(EntityMessage::Is_Jumping);
                message.m_receiver = entity;
                m_system_manager->get_message_handler()->dispatch(message);
            }
            
        }
    }

    void StateSystem::handle_event(EntityId entity, EntityEvent event)
    {
        switch (event)
        {
        case EntityEvent::Became_Idle:
            change_state(entity, EntityState::Idle, false);
            break;
        
        default:
            break;
        }       
    }

    void StateSystem::notify(const Message& message)
    {
        if (has_entity(message.m_receiver))
        {
            EntityMessage entity_message = message.m_type;

            switch (entity_message)
            {
            case EntityMessage::Move:
                {
                    auto state_component = m_system_manager->get_entity_manager()->get_component<StateComponent>(message.m_receiver,ComponentType::State);

                    if (state_component->get_state() == EntityState::Dying)
                    {
                        return;
                    }

                    EntityEvent event;

                    if (std::get<Direction>(message.m_data) == Direction::Up)
                    {
                        event = EntityEvent::Moving_Up;
                    }
                    else if (std::get<Direction>(message.m_data) == Direction::Down)
                    {
                        event = EntityEvent::Moving_Down;
                    }
                    else if (std::get<Direction>(message.m_data) == Direction::Left)
                    {
                        event = EntityEvent::Moving_Left;
                    }
                    else if (std::get<Direction>(message.m_data) == Direction::Right)
                    {
                        event = EntityEvent::Moving_Right;
                    }

                    m_system_manager->add_event(message.m_receiver, event);

                    change_state(message.m_receiver, EntityState::Walking, false);
                }
                break;

            case EntityMessage::Switch_State:
                change_state(message.m_receiver, std::get<EntityState>(message.m_data), false);
                break;

            case EntityMessage::Jump:
                {
                    auto state_component = m_system_manager->get_entity_manager()->get_component<StateComponent>(message.m_receiver,ComponentType::State);

                    if (state_component->get_state() == EntityState::Jumping || state_component->get_state() == EntityState::Dying)
                    {
                        return;
                    }

                    EntityEvent event = EntityEvent::Jumping;
                    m_system_manager->add_event(message.m_receiver, event);
                    change_state(message.m_receiver, EntityState::Jumping, false);
                }
                break;
            
            default:
                break;
            }
        }        
    }

    void StateSystem::change_state(EntityId id, EntityState state, bool force)
    {
        auto entity_manager = m_system_manager->get_entity_manager();
        auto state_component = entity_manager->get_component<StateComponent>(id, ComponentType::State);

        if (!force && state_component->get_state() == EntityState::Dying)
        {
            return;
        }
        
        state_component->set_state(state);

        Message message(EntityMessage::State_Changed);
        message.m_receiver = id;
        message.m_data = state;

        m_system_manager->get_message_handler()->dispatch(message);
    }
} // namespace Engine
