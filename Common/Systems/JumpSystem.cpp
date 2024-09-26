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

            // jump_step(time, jump_component);
            // position_component->move_by({0.f,jump_component->get_jump_velocity()*time});
        }
    }

    void JumpSystem::handle_event(EntityId entity, EntityEvent event)
    {

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
                if (jump_component->get_jump_velocity()!=0.f)
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

    void JumpSystem::jump_step(float time, std::shared_ptr<JumpComponent> jump_component)
    {
        jump_component->apply_gravity(m_map->get_gravity());

    }

    void JumpSystem::set_map(std::shared_ptr<LayeredMap> map)
    {
        m_map = map;
    }
} // namespace Engine
