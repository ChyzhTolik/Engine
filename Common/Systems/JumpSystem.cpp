#include "JumpSystem.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"

namespace Engine
{
    JumpSystem::JumpSystem(std::shared_ptr<SystemManager> system_manager): System(SystemType::Jump, system_manager)
    {
    }
    
    JumpSystem::~JumpSystem()
    {
    }

    void JumpSystem::subscribe()
    {
        m_system_manager->get_message_handler()->subscribe(EntityMessage::Jump_Action, shared_from_this());
    }

    void JumpSystem::update(float time)
    {
        for (auto &&entity : m_entities)
        {
            jump();
        }
    }

    void JumpSystem::handle_event(EntityId entity, EntityEvent event)
    {

    }

    void JumpSystem::notify(const Message& message)
    {

    }

    void JumpSystem::jump()
    {
        auto position_component = m_system_manager->get_entity_manager()->get_component<PositionComponent>(0, ComponentType::Position);
        position_component->set_position({200.f,200.f});
    }
} // namespace Engine
