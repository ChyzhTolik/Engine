#include "JumpSystem.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "LayeredMap.hpp"
#include "PositionComponent.hpp"

namespace Engine
{
    JumpSystem::JumpSystem(std::shared_ptr<SystemManager> system_manager): System(SystemType::Jump, system_manager), m_map(nullptr)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::Position));
        mask.set(static_cast<size_t>(ComponentType::Jump));

        m_required_components.push_back(mask);
    }
    
    JumpSystem::~JumpSystem()
    {
    }

    void JumpSystem::subscribe()
    {
        m_system_manager->get_message_handler()->subscribe(EntityMessage::Is_Jumping, shared_from_this());
    }

    void JumpSystem::update(float time)
    {
        auto entities_manager = m_system_manager->get_entity_manager();

        for (auto &&entity : m_entities)
        {
            auto position_component = entities_manager->get_component<PositionComponent>(entity, ComponentType::Position);
            auto jump_component = entities_manager->get_component<JumpComponent>(entity, ComponentType::Jump);

            apply_gravity(time, jump_component);
            auto pos = position_component->get_position();
            pos.y -= m_jump_velocity*time;
            position_component->set_position(pos);

            std::string position_text = "Position =("+std::to_string(position_component->get_position().x)+","
                +std::to_string(position_component->get_position().y)+".";
            m_system_manager->get_infobox()->Add(position_text);
            m_system_manager->get_infobox()->Add("Velocity=" + std::to_string(m_jump_velocity));
        }
    }

    void JumpSystem::handle_event(EntityId entity, EntityEvent event)
    {
        switch (event)
        {
        case EntityEvent::Colliding_Y:
        {
            auto entity_manager = m_system_manager->get_entity_manager();
            auto jump_component = entity_manager->get_component<JumpComponent>(entity,ComponentType::Jump);
            jump_component->set_grounded(true);
        }
            break;
        
        default:
            break;
        }
    }

    void JumpSystem::notify(const Message& message)
    {
        auto entity_manager = m_system_manager->get_entity_manager();
        EntityMessage message_type = message.m_type;

        switch (message_type)
        {
            case EntityMessage::Is_Jumping:
            {
                if (!has_entity(message.m_receiver))
                {
                    return;
                }
                
                auto jump_component = entity_manager->get_component<JumpComponent>(message.m_receiver,ComponentType::Jump);
                if (!jump_component->is_grounded())
                {
                    return;
                }
                
                m_system_manager->add_event(message.m_receiver, EntityEvent::Became_Idle);
            }
            break;
        
        default:
            break;
        }
    }

    void JumpSystem::apply_gravity(float time, std::shared_ptr<JumpComponent> jump_component)
    {
        m_jump_velocity = jump_component->get_jump_velocity();
        const auto mass = jump_component->get_mass();
        
        m_jump_velocity -= mass*m_gravity*time;
        if (jump_component->is_grounded())
        {
            m_jump_velocity = 0;
        }
        
        jump_component->set_jump_velocity(m_jump_velocity);
    }

    void JumpSystem::set_map(std::shared_ptr<LayeredMap> map)
    {
        m_map = map;
    }
} // namespace Engine
