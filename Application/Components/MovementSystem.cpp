#include "MovementSystem.hpp"

#include <bitset>
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "TileMap.hpp"

namespace Engine
{
    MovementSystem::MovementSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::Movement, l_system_manager)
    {
        std::bitset<REQUIREMENTS_NUM> req;
        req.set((unsigned int)ComponentType::Position);
        req.set((unsigned int)ComponentType::Movable);
        m_requiredComponents.push_back(req);
        req.reset();
        m_system_manager->GetMessageHandler().Subscribe(EntityMessage::Is_Moving,shared_from_this());
        m_gameMap = nullptr;
    }
    
    MovementSystem::~MovementSystem()
    {
    }

    void MovementSystem::Update(float l_dT)
    {
        if (!m_gameMap)
        { 
            return; 
        }

        auto entities = m_system_manager->GetEntityManager();

        for(auto &entity : m_entities)
        {
            auto position = entities-> GetComponent<PositionComp>(entity, ComponentType::Position);
            auto movable = entities-> GetComponent<MovableComponent>(entity, ComponentType::Movable);
            MovementStep(l_dT, movable, position);
            position->MoveBy(movable->get_velocity() * l_dT);
        }
    }

    void MovementSystem::MovementStep(float l_dT, std::shared_ptr<MovableComponent> l_movable, std::shared_ptr<PositionComp> l_position)
    {
        sf::Vector2f f_coefficient = GetTileFriction(l_position->get_elevation(),
            floor(l_position->get_position().x / Sheet::Tile_Size), 
            floor(l_position->get_position().y / Sheet::Tile_Size));

        sf::Vector2f friction(l_movable->get_speed().x * f_coefficient.x, l_movable->get_speed().y * f_coefficient.y);

        l_movable->add_velocity(l_movable->get_acceleration() * l_dT);
        l_movable->set_acceleration(sf::Vector2f(0.0f, 0.0f));
        l_movable->apply_friction(friction * l_dT);

        float magnitude = sqrt(
            (l_movable->get_velocity().x * l_movable->get_velocity().x) +
            (l_movable->get_velocity().y * l_movable->get_velocity().y)
        );

        if (magnitude <= l_movable->get_max_velocity())
        { 
            return;
        }

        float max_V = l_movable->get_max_velocity();

        l_movable->set_velocity(sf::Vector2f
        (
            (l_movable->get_velocity().x / magnitude) * max_V,
            (l_movable->get_velocity().y / magnitude) * max_V
        ));
    }

    const sf::Vector2f& MovementSystem::GetTileFriction(uint32_t l_elevation, uint32_t l_x, uint32_t l_y)
    {
        std::shared_ptr<Tile> t = m_gameMap->get_tile_on_layer(l_x, l_y, l_elevation);

        return(t ? t->m_tile_info.friction : m_gameMap->GetDefaultTile()->friction);
    }

    void MovementSystem::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event)
    {
        switch(l_event)
        {
            case EntityEvent::Colliding_X:
            StopEntity(l_entity,Axis::x); 
            break;

            case EntityEvent::Colliding_Y:
            StopEntity(l_entity, Axis::y); 
            break;

            case EntityEvent::Moving_Left:
            SetDirection(l_entity, Direction::Left); 
            break;

            case EntityEvent::Moving_Right:
            SetDirection(l_entity, Direction::Right); 
            break;

            case EntityEvent::Moving_Up:
            {
                auto mov = m_system_manager->GetEntityManager()-> GetComponent<MovableComponent>(l_entity,ComponentType::Movable);

                if(mov->get_velocity().x == 0)
                {
                    SetDirection(l_entity, Direction::Up);
                }
            }
            break;

            case EntityEvent::Moving_Down:
            {
                auto mov = m_system_manager->GetEntityManager()->GetComponent<MovableComponent>(l_entity,ComponentType::Movable);

                if(mov->get_velocity().x == 0)
                {
                    SetDirection(l_entity, Direction::Down);
                }
            }
            break;
        }
    }

    void MovementSystem::Notify(const Message& l_message)
    {
        auto eMgr = m_system_manager->GetEntityManager();        
        EntityMessage m = (EntityMessage)l_message.m_type;

        switch(m)
        {
            case EntityMessage::Is_Moving:
            {
                if (!HasEntity(l_message.m_receiver))
                { 
                    return; 
                }

                auto movable = eMgr->GetComponent<MovableComponent>(l_message.m_receiver, ComponentType::Movable);

                if (movable->get_velocity() != sf::Vector2f(0.0f, 0.0f))
                {
                    return;
                }

                m_system_manager->AddEvent(l_message.m_receiver, (EventID)EntityEvent::Became_Idle);
            }
            break;

        default:
            break;;
        }
    }

    void MovementSystem::StopEntity(const EntityId& l_entity, const Axis& l_axis)
    {
        auto movable = m_system_manager->GetEntityManager()->GetComponent<MovableComponent>(l_entity,ComponentType::Movable);

        if(l_axis == Axis::x)
        {
            movable->set_velocity(sf::Vector2f(0.f, movable->get_velocity().y));
        } 
        else if (l_axis == Axis::y)
        {
            movable->set_velocity(sf::Vector2f(movable->get_velocity().x, 0.f));
        }
    }

    void MovementSystem::SetDirection(const EntityId& l_entity, const Direction& l_dir)
    {
        auto movable = m_system_manager->GetEntityManager()->GetComponent<MovableComponent>(l_entity,ComponentType::Movable);
        movable->set_direction(l_dir);
        Message msg((MessageType)EntityMessage::Direction_Changed);
        msg.m_receiver = l_entity;
        msg.m_info = (int)l_dir;
        m_system_manager->GetMessageHandler().Dispatch(msg);
    }

    void MovementSystem::SetMap(std::shared_ptr<TileMap> l_gameMap)
    { 
        m_gameMap = l_gameMap; 
    }
} // namespace Engine
