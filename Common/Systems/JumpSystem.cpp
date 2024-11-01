#include "JumpSystem.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "LayeredMap.hpp"
#include "MovableComponent.hpp"

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

            if (!have_tile_above_or_below(entity,position_component, collidable_component).below)
            {
                if (jump_component->is_grounded())
                {
                    jump_component->set_grounded(false);
                    Message msg(EntityMessage::Fall);
                    msg.m_receiver = entity;
                    m_system_manager->get_message_handler()->dispatch(msg);
                }                
            }            

            std::string position_text = "Position =("+std::to_string(position_component->get_position().x)+","
                +std::to_string(position_component->get_position().y)+".";
            // m_system_manager->get_infobox()->Add(position_text);
            // m_system_manager->get_infobox()->Add("Velocity=" + std::to_string(m_jump_velocity));
        }
    }

    void JumpSystem::handle_event(EntityId entity, EntityEvent event)
    {
        switch (event)
        {
        case EntityEvent::Colliding_Y:
        {
            auto logger = m_system_manager->get_logger();
            logger->info("Colliding_Y");
            auto entity_manager = m_system_manager->get_entity_manager();            

            auto position_component = entity_manager->get_component<PositionComponent>(entity, ComponentType::Position);
            auto collidable_component = entity_manager->get_component<CollidableComponent>(entity, ComponentType::Collidable);
            const auto is_colliding_y = check_collision_with_wall_during_jump_or_fall(entity);
            if (is_colliding_y)
            {
                auto jump_component = entity_manager->get_component<JumpComponent>(entity,ComponentType::Jump);
                jump_component->set_grounded(true);
                m_system_manager->add_event(entity, EntityEvent::Became_Idle);
            }
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

    JumpSystem::NoTileVertically JumpSystem::have_tile_above_or_below(EntityId entity, 
        std::shared_ptr<PositionComponent> position_component, 
        std::shared_ptr<CollidableComponent> collidable)
    {
        NoTileVertically result{false,false};
        auto entities_manager = m_system_manager->get_entity_manager();
        auto jump_component = entities_manager->get_component<JumpComponent>(entity, ComponentType::Jump);
        if (!jump_component->is_grounded())
        {
            result = {false,true};
            return result;
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
                result.below = true;
            }
        }

        for (auto x = from_x; x <= to_x; x++)
        {
            auto tile = m_map->get_tile(position_component->get_elevation(), {static_cast<int>(x), static_cast<int>(y - 1)});
            if (!tile)
            {
                continue;
            }
            else
            {          
                result.above = true;
            }
        }
        
        return result;
    }

    bool JumpSystem::check_collision_with_wall_during_jump_or_fall(EntityId entity)
    {
        auto entities_manager = m_system_manager->get_entity_manager();
        auto jump_component = entities_manager->get_component<JumpComponent>(entity, ComponentType::Jump);

        if (jump_component->is_grounded())
        {
            return false;
        }

        auto collidable = entities_manager->get_component<CollidableComponent>(entity, ComponentType::Collidable);
        const auto tile_size = m_map->get_tile_size();
        const auto entity_rect = collidable->get_bounding_box();
        const uint32_t from_x = floor(entity_rect.left / m_map->get_tile_size().x);
        const uint32_t to_x = floor((entity_rect.left + entity_rect.width) / m_map->get_tile_size().x);
        const uint32_t y = floor(entity_rect.top / m_map->get_tile_size().y);

        auto move_component = entities_manager->get_component<MovableComponent>(entity, ComponentType::Movable);
        auto direction = move_component->get_direction();
        
        uint32_t x{from_x};

        if (direction==Direction::Left)
        {
            x = to_x;
        }

        auto position_component = entities_manager->get_component<PositionComponent>(entity, ComponentType::Position);
        auto tile = m_map->get_tile(position_component->get_elevation(), {static_cast<int>(x), static_cast<int>(y + 1)});

        if (tile)
        {
            return true;
        }

        tile = m_map->get_tile(position_component->get_elevation(), {static_cast<int>(x), static_cast<int>(y - 1)});
        if (tile)
        {
            return true;
        }

        if (m_jump_velocity<=0)
        {
            if (direction==Direction::Left)
            {
                x = from_x;
            }
            else
            {
                x = to_x;
            }
            tile = m_map->get_tile(position_component->get_elevation(), {static_cast<int>(x), static_cast<int>(y + 1)});
            if (tile)
            {
                return true;
            }
        }
        

        return false;
    }
} // namespace Engine
