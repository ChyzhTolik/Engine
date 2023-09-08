#include "ControllerSystem.hpp"

#include "Component.hpp"
#include "MovableComponent.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"

namespace Engine
{
    ControllerSystem::ControllerSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::Control, l_system_manager)
    {
        std::bitset<REQUIREMENTS_NUM> req;
        req.set((unsigned int)ComponentType::Position);
        req.set((unsigned int)ComponentType::Movable);
        req.set((unsigned int)ComponentType::Controller);
        m_requiredComponents.push_back(req);
    }
    
    ControllerSystem::~ControllerSystem()
    {
    }

    void ControllerSystem::Update(float l_dT)
    {

    }

    void ControllerSystem::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event)
    {
        switch(l_event)
        {
            case EntityEvent::Moving_Left:
                MoveEntity(l_entity,Direction::Left); 
                break;

            case EntityEvent::Moving_Right:
                MoveEntity(l_entity, Direction::Right); 
                break;

            case EntityEvent::Moving_Up:
                MoveEntity(l_entity, Direction::Up); 
                break;

            case EntityEvent::Moving_Down:
                MoveEntity(l_entity, Direction::Down); 
                break;

            default:
                break;
        }
    }

    void ControllerSystem::MoveEntity(const EntityId& l_entity, const Direction& l_dir)
    {
        auto mov = m_system_manager->GetEntityManager()->GetComponent<MovableComponent>(l_entity, ComponentType::Movable);
        mov->move(l_dir);
    }

    void ControllerSystem::Notify(const Message& l_message)
    {

    }
} // namespace Engine
