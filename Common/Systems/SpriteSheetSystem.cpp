#include "SpriteSheetSystem.hpp"

#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "DrawableComponentInterface.hpp"
#include "StateComponent.hpp"

namespace Engine
{
    SpriteSheetSystem::SpriteSheetSystem(std::shared_ptr<SystemManager> system_manager) : System(SystemType::SheetAnimation, system_manager)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::State));
        mask.set(static_cast<size_t>(ComponentType::SpriteSheet));

        m_required_components.push_back(mask);
    }
    
    SpriteSheetSystem::~SpriteSheetSystem()
    {
    }

    void SpriteSheetSystem::subscribe()
    {
        m_system_manager->get_message_handler()->subscribe(EntityMessage::State_Changed, shared_from_this());
    }

    void SpriteSheetSystem::update(float time)
    {
        auto entities_manager = m_system_manager->get_entity_manager();

        for (auto &&entity : m_entities)
        {
            auto drawable_component = entities_manager->get_component<DrawableComponentInterface>(entity, ComponentType::SpriteSheet);
            auto state_component = m_system_manager->get_entity_manager()->get_component<StateComponent>(entity,ComponentType::State);

            auto sprite_sheet = drawable_component->get_sprite_sheet();
            sprite_sheet->Update(time);

            auto animation = sprite_sheet->GetCurrentAnim();

            if (animation->)
            {
                /* code */
            }
            
        }
    }

    void SpriteSheetSystem::handle_event(EntityId entity, EntityEvent event)
    {
        
    }
    
    void SpriteSheetSystem::notify(const Message& message)
    {
        
    }
    
} // namespace Engine
