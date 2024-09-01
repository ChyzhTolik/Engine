#include "JumpSystem.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "LayeredMap.hpp"

namespace Engine
{
    JumpSystem::JumpSystem(std::shared_ptr<SystemManager> system_manager): System(SystemType::Jump, system_manager), m_map(nullptr)
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
        auto entities_manager = m_system_manager->get_entity_manager();

        for (auto &&entity : m_entities)
        {
            auto position_component = entities_manager->get_component<PositionComponent>(entity, ComponentType::Position);
            auto jump_component = entities_manager->get_component<JumpComponent>(entity, ComponentType::Jump);

            jump_step(time, movable_component, position_component);
            position_component->move_by(jump_component->get_jump_velocity()*time);
        }
    }

    void JumpSystem::handle_event(EntityId entity, EntityEvent event)
    {

    }

    void JumpSystem::notify(const Message& message)
    {

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
