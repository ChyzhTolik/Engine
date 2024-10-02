#include "JumpSystem.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "LayeredMap.hpp"

namespace Engine
{
    JumpSystem::JumpSystem(std::shared_ptr<SystemManager> system_manager): System(SystemType::Jump, system_manager), m_map(nullptr)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::Position));
        mask.set(static_cast<size_t>(ComponentType::Jump));
        mask.set(static_cast<size_t>(ComponentType::Collidable));

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

            auto collidable_component = entities_manager->get_component<CollidableComponent>(entity, ComponentType::Collidable);
            check_no_tile_below(entity,position_component, collidable_component);

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
            m_system_manager->add_event(entity, EntityEvent::Became_Idle);
        }
            break;

        case EntityEvent::Falling:
        {
            auto entity_manager = m_system_manager->get_entity_manager();
            auto jump_component = entity_manager->get_component<JumpComponent>(entity,ComponentType::Jump);
            jump_component->set_grounded(false);
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

    void JumpSystem::check_no_tile_below(EntityId entity, std::shared_ptr<PositionComponent> position_component, std::shared_ptr<CollidableComponent> collidable)
    {
        auto entities_manager = m_system_manager->get_entity_manager();
        auto jump_component = entities_manager->get_component<JumpComponent>(entity, ComponentType::Jump);
        if (!jump_component->is_grounded())
        {
            return;
        }

        auto tile_size = m_map->get_tile_size();
        auto entity_rect = collidable->get_bounding_box();
        uint32_t from_x = floor(entity_rect.left / m_map->get_tile_size().x);
        uint32_t to_x = floor((entity_rect.left + entity_rect.width) / m_map->get_tile_size().x);
        uint32_t y = floor(entity_rect.top / m_map->get_tile_size().y);

        for (auto x = from_x; x <= to_x; x++)
        {
            auto tile = m_map->get_tile(position_component->get_elevation(), {static_cast<int>(x), static_cast<int>(y + 1)});
            if (!tile)
            {
                continue;
            }
            else
            {
                return;
            }
        }
        
        jump_component->set_grounded(false);

        Message msg(EntityMessage::Fall);

        msg.m_receiver = entity;

        m_system_manager->get_message_handler()->dispatch(msg);
    }
} // namespace Engine
