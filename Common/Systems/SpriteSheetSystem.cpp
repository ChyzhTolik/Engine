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

            m_system_manager->get_infobox()->Add("Time:"+std::to_string(time));

            auto animation = sprite_sheet->GetCurrentAnim();

            if (animation->is_attack())
            {
                m_system_manager->get_infobox()->Add("Attack animation");
                if (!sprite_sheet->GetCurrentAnim()->is_playing())                
                {
                    Message message(EntityMessage::Switch_State);
                    message.m_receiver = entity;
                    message.m_data = EntityState::Idle;
                    m_system_manager->get_message_handler()->dispatch(message);
                }
                else if (sprite_sheet->GetCurrentAnim()->IsInAction())
                {   
                    Message message(EntityMessage::Attack_Action);
                    message.m_sender = entity;
                    m_system_manager->get_message_handler()->dispatch(message);
                }
            }
            else if (animation->is_death())
            {
                if (!sprite_sheet->GetCurrentAnim()->is_playing())
                {
                    Message message(EntityMessage::Switch_State);
                    message.m_receiver = entity;
                    message.m_data = EntityState::Idle;
                    m_system_manager->get_message_handler()->dispatch(message);
                }
                else
                {
                    Message message(EntityMessage::Dead);
                    message.m_receiver = entity;
                    m_system_manager->get_message_handler()->dispatch(message);    
                }
            }
        }
    }

    void SpriteSheetSystem::handle_event(EntityId entity, EntityEvent event)
    {
        
    }
    
    void SpriteSheetSystem::notify(const Message& message)
    {
        if (has_entity(message.m_receiver))
        {
            if (m_callbacks.find(message.m_receiver)==m_callbacks.end())
            {
                return;
            }          

            switch (message.m_type)
            {
            case EntityMessage::State_Changed:
                {
                    EntityState state = std::get<EntityState>(message.m_data);
                    switch (state)
                    {
                    case EntityState::Idle:
                        m_callbacks.at(message.m_receiver)(state, true, true);
                        break;
                    
                    case EntityState::Walking:
                        m_callbacks.at(message.m_receiver)(state, true, true);
                        break;

                    case EntityState::Attacking:
                        m_callbacks.at(message.m_receiver)(state, true,false);
                        break;

                    case EntityState::Hurt:
                        break;

                    case EntityState::Dying:
                        m_callbacks.at(message.m_receiver)(state, true,false);
                        break;

                    case EntityState::Jumping:
                        m_callbacks.at(message.m_receiver)(state, true,false);
                        break;

                    default:
                        break;
                    }
                }
                break;
            
            default:
                break;
            }
        }
    }
    
    void SpriteSheetSystem::set_change_animation_callback(EntityId id, ChangeAnimationCallback callback)
    {
        m_callbacks[id] = callback;
    }
} // namespace Engine
