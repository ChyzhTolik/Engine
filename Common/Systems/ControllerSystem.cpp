#include "ControllerSystem.hpp"

#include "SystemManager.hpp"
#include "MovableComponent.hpp"
#include "EntitiesManager.hpp"

namespace Engine
{
    ControllerSystem::ControllerSystem(std::shared_ptr<SystemManager> system_manager) : System(SystemType::Control, system_manager)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::Position));
        mask.set(static_cast<size_t>(ComponentType::Movable));
        mask.set(static_cast<size_t>(ComponentType::Controller));

        m_required_components.push_back(mask);
    }

    void ControllerSystem::subscribe()
    {

    }
    
    ControllerSystem::~ControllerSystem()
    {
    }

    void ControllerSystem::handle_event(EntityId entity, EntityEvent event)
    {
        switch (event)
        {
        case EntityEvent::Moving_Left:
            move_entity(entity,Direction::Left);
            break;

        case EntityEvent::Moving_Right:
            move_entity(entity,Direction::Right);
            break;
        
        case EntityEvent::Moving_Up:
            move_entity(entity,Direction::Up);
            break;

        case EntityEvent::Moving_Down:
            move_entity(entity,Direction::Down);
            break;

        case EntityEvent::Jumping:
            jump_entity(entity);
            break;
        
        default:
            break;
        }
    }

    void ControllerSystem::move_entity(EntityId entity, Direction direction)
    {
        auto movable_component = m_system_manager->get_entity_manager()->get_component<MovableComponent>(entity, ComponentType::Movable);

        movable_component->move(direction);
    }

    void ControllerSystem::jump_entity(EntityId entity)
    {
        auto movable_component = m_system_manager->get_entity_manager()->get_component<MovableComponent>(entity, ComponentType::Movable);

        movable_component->jump();
    }

    void ControllerSystem::update(float time)
    {

    }

    void ControllerSystem::notify(const Message& message)
    {
        
    }
} // namespace Engine
