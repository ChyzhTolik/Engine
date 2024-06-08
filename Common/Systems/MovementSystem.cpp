#include "MovementSystem.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "LayeredMap.hpp"

namespace Engine
{
    MovementSystem::MovementSystem(std::shared_ptr<SystemManager> system_manager) : System(SystemType::Movement, system_manager), m_map(nullptr)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::Position));
        mask.set(static_cast<size_t>(ComponentType::Movable));

        m_required_components.push_back(mask);
    }

    void MovementSystem::subscribe()
    {
        m_system_manager->get_message_handler()->subscribe(EntityMessage::Is_Moving, shared_from_this());
    }
    
    MovementSystem::~MovementSystem()
    {
    }

    void MovementSystem::set_map(std::shared_ptr<LayeredMap> map)
    {
        m_map = map;
    }

    void MovementSystem::update(float time)
    {
        if (!m_map)
        {
            return;
        }
        
        auto entities_manager = m_system_manager->get_entity_manager();

        for (auto &&entity : m_entities)
        {
            auto position_component = entities_manager->get_component<PositionComponent>(entity, ComponentType::Position);
            auto movable_component = entities_manager->get_component<MovableComponent>(entity, ComponentType::Movable);

            movement_step(time, movable_component, position_component);
            position_component->move_by(movable_component->get_velocity()*time);
        }
    }

    void MovementSystem::movement_step(float time, std::shared_ptr<MovableComponent> movable, std::shared_ptr<PositionComponent> position)
    {
        sf::Vector2f coefficient = get_tile_friction(position->get_elevation(),
            floor(position->get_position().x/m_map->get_map_size().x), floor(position->get_position().y/m_map->get_tile_size().y));

        sf::Vector2f friction(movable->get_speed().x*coefficient.x, movable->get_speed().y*coefficient.y);

        movable->add_velocity(movable->get_acceleration()*time);
        movable->set_acceleration({0.f,0.f});
        movable->apply_friction(friction*time);

        float magnitude = sqrt((movable->get_velocity().x * movable->get_velocity().x) +
            (movable->get_velocity().y * movable->get_velocity().y));

        if (magnitude<=movable->get_max_velocity())
        {
            return;
        }

        float max_V = movable->get_max_velocity();
        movable->set_velocity({movable->get_velocity().x / magnitude * max_V,
            movable->get_velocity().y / magnitude * max_V});        
    }

    const sf::Vector2f MovementSystem::get_tile_friction(u_int32_t elevation, int x, int y)
    {
        auto tile = m_map->get_tile(elevation,{x,y});

        while (!tile && elevation>0)
        {
            elevation--;
            tile = m_map->get_tile(elevation,{x,y});
        }
        
        return (tile ? tile->get_friction():m_map->get_default_friction());
    }

    void MovementSystem::handle_event(EntityId entity, EntityEvent event)
    {
        switch (event)
        {
        case EntityEvent::Colliding_X:
            stop_entity(entity,Axis::x);
            break;

        case EntityEvent::Colliding_Y:
            stop_entity(entity,Axis::y);
            break;

        case EntityEvent::Moving_Left:
            set_direction(entity,Direction::Left);
            break;

        case EntityEvent::Moving_Right:
            set_direction(entity,Direction::Right);
            break;
        
        case EntityEvent::Moving_Up:
        {
            auto movable_component = m_system_manager->get_entity_manager()->get_component<MovableComponent>(entity, ComponentType::Movable);

            if (movable_component->get_velocity().x == 0)
            {
                set_direction(entity,Direction::Up);                
            }
        }
            break;

        case EntityEvent::Moving_Down:
        {
            auto movable_component = m_system_manager->get_entity_manager()->get_component<MovableComponent>(entity, ComponentType::Movable);

            if (movable_component->get_velocity().x == 0)
            {
                set_direction(entity,Direction::Down);                
            }
        }

            break;
        
        default:
            break;
        }
    }

    void MovementSystem::notify(const Message& message)
    {
        auto entity_manager = m_system_manager->get_entity_manager();
        EntityMessage message_type = message.m_type;

        switch (message_type)
        {
        case EntityMessage::Is_Moving:
            {
                if (!has_entity(message.m_receiver))
                {
                    return;
                }
                
                auto movable = entity_manager->get_component<MovableComponent>(message.m_receiver,ComponentType::Movable);
                if (movable->get_velocity()!=sf::Vector2f{0.f,0.f})
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

    void MovementSystem::stop_entity(EntityId entity, Axis axis)
    {
        auto entity_manager = m_system_manager->get_entity_manager();
        auto movable = entity_manager->get_component<MovableComponent>(entity,ComponentType::Movable);

        if (axis == Axis::x)
        {
            movable->set_velocity({0.f, movable->get_velocity().y});
        }
        else if (axis == Axis::y)
        {
            movable->set_velocity({movable->get_velocity().x, 0.f});
        }
    }

    void MovementSystem::set_direction(EntityId entity, Direction direction)
    {
        auto entity_manager = m_system_manager->get_entity_manager();
        auto movable = entity_manager->get_component<MovableComponent>(entity,ComponentType::Movable);

        movable->set_direction(direction);

        Message message(EntityMessage::Direction_Changed);
        message.m_receiver=entity;
        message.m_data = direction;
        m_system_manager->get_message_handler()->dispatch(message);
    }
} // namespace Engine
