#include "RendererSystem.hpp"

#include "EntitiesManager.hpp"
#include "SystemManager.hpp"
#include "PositionComponent.hpp"
#include "DrawableComponentInterface.hpp"
#include "SpriteSheetComponent.hpp"
#include "AnimationTypes.hpp"

namespace Engine
{
    RendererSystem::RendererSystem(std::shared_ptr<SystemManager> system_manager) : System(SystemType::Renderer, system_manager)
    {
        ComponentBitSet mask;
        mask.set(static_cast<size_t>(ComponentType::Position));
        mask.set(static_cast<size_t>(ComponentType::SpriteSheet));

        m_required_components.push_back(mask);
    }
    
    void RendererSystem::subscribe()
    {
        m_system_manager->get_message_handler()->subscribe(EntityMessage::Direction_Changed, shared_from_this());
    }

    RendererSystem::~RendererSystem()
    {
        
    }

    void RendererSystem::update(float time)
    {
        auto entity_manager = m_system_manager->get_entity_manager();

        for (auto&& entity : m_entities)
        {
            auto position_component = entity_manager->get_component<PositionComponent>(entity, ComponentType::Position);
            std::shared_ptr<DrawableComponentInterface> drawable_component = nullptr;

            if (entity_manager->has_component(entity,ComponentType::SpriteSheet))
            {
                drawable_component = entity_manager->get_component<DrawableComponentInterface>(entity,ComponentType::SpriteSheet);
            }
            else
            {
                continue;
            }

            drawable_component->update_position(position_component->get_position());
            drawable_component->update(time);
        }
    }

    void RendererSystem::handle_event(EntityId entity, EntityEvent event)
    {
        if (event == EntityEvent::Moving_Left ||
            event == EntityEvent::Moving_Right ||
            event == EntityEvent::Moving_Up ||
            event == EntityEvent::Moving_Down ||
            event == EntityEvent::Elevation_Change ||
            event == EntityEvent::Spawned
        )
        {
            sort_drawables();
        }
        
    }

    void RendererSystem::notify(const Message& message)
    {
        if (has_entity(message.m_receiver))
        {
            EntityMessage entity_message = message.m_type;

            switch (entity_message)
            {
            case EntityMessage::Direction_Changed:
                set_sprite_sheet_direction(message.m_receiver, Direction(std::get<uint32_t>(message.m_data)));
                break;
            
            default:
                break;
            }
        }        
    }
    
    void RendererSystem::render(std::shared_ptr<Window> window, uint16_t layer)
    {
        auto entities_manager = m_system_manager->get_entity_manager();

        for (auto &&entity : m_entities)
        {
            auto position_component = entities_manager->get_component<PositionComponent>(entity,ComponentType::Position);

            if (position_component->get_elevation()<layer)
            {
                continue;
            }

            if (position_component->get_elevation()>layer)
            {
                break;
            }
            
            std::shared_ptr<DrawableComponentInterface> drawable_component = nullptr;

            if (!entities_manager->has_component(entity,ComponentType::SpriteSheet))
            {
                continue;
            }

            drawable_component = entities_manager->get_component<DrawableComponentInterface>(entity,ComponentType::SpriteSheet);

            sf::FloatRect bounds;

            bounds.left = position_component->get_position().x - drawable_component->get_size().x/2;
            bounds.top = position_component->get_position().y - drawable_component->get_size().y/2;
            bounds.width = drawable_component->get_size().x;
            bounds.height = drawable_component->get_size().y;

            if (!window->GetViewSpace().findIntersection(bounds).has_value())
            {
                continue;
            }
            
            drawable_component->draw(window->GetRenderWindow());
        }
        
    }
    
    void RendererSystem::sort_drawables()
    {
        auto entities_manager = m_system_manager->get_entity_manager();

        std::sort(m_entities.begin(),m_entities.end(),[entities_manager](EntityId m1, EntityId m2){
            auto position_component1 = entities_manager->get_component<PositionComponent>(m1,ComponentType::Position);
            auto position_component2 = entities_manager->get_component<PositionComponent>(m2,ComponentType::Position);

            if (position_component1->get_elevation() == position_component2->get_elevation())
            {
                return position_component1->get_position().y < position_component2->get_position().y;
            }

            return position_component1->get_elevation() < position_component2->get_elevation();
        });
    }
    
    void RendererSystem::set_sprite_sheet_direction(EntityId id, Direction dir)
    {
        auto entities_manager = m_system_manager->get_entity_manager();

        if (!entities_manager->has_component(id, ComponentType::SpriteSheet))
        {
            return;
        }
        
        auto sprite_sheet = entities_manager->get_component<SpriteSheetComponent<KnightAnimations>>(id, ComponentType::SpriteSheet);

        sprite_sheet->get_sprite_sheet()->SetDirection(dir);
    }
    
} // namespace Engine
