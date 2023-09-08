#include "RendererSystem.hpp"
#include "Component.hpp"
#include "EntityMessages.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "PositionComp.hpp"
#include "DrawableComponent.hpp"
#include "SpriteSheetComponent.hpp"

namespace Engine
{
    RendererSystem::RendererSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::Renderer, l_system_manager)
    {
        std::bitset<REQUIREMENTS_NUM> req;
        req.set((unsigned int)ComponentType::Position);
        req.set((unsigned int)ComponentType::SpriteSheet);
        m_requiredComponents.push_back(req);
        req.reset();
        m_system_manager->GetMessageHandler().Subscribe(EntityMessage::Direction_Changed,std::dynamic_pointer_cast<Observer>(shared_from_this()));
    }
    
    RendererSystem::~RendererSystem()
    {
    }

    void RendererSystem::Render(std::shared_ptr<Window> l_wind, uint32_t l_layer)
    {
        auto entities = m_system_manager->GetEntityManager();

        for(auto &entity : m_entities)
        {
            auto position = entities->GetComponent<PositionComp>(entity, ComponentType::Position);

            if(position->get_elevation() < l_layer)
            { 
                continue; 
            }

            if(position->get_elevation() > l_layer)
            { 
                break; 
            }

            std::shared_ptr<DrawableComponent> drawable = nullptr;

            if (!entities->HasComponent(entity, ComponentType::SpriteSheet))
            {
                continue;
            }

            drawable = entities->GetComponent<DrawableComponent>(entity, ComponentType::SpriteSheet);
            sf::FloatRect drawableBounds;
            drawableBounds.left = position->get_position().x - (drawable->GetSize().x / 2);
            drawableBounds.top = position->get_position().y - drawable->GetSize().y;
            drawableBounds.width = drawable->GetSize().x;
            drawableBounds.height = drawable->GetSize().y;

            if (!l_wind->GetViewSpace().findIntersection(drawableBounds))
            {
                continue;
            }

            drawable->Draw(l_wind->GetRenderWindow());
        }
    }

    void RendererSystem::Update(float l_dT)
    {
        auto entities = m_system_manager->GetEntityManager();

        for(auto &entity : m_entities)
        {
            auto position = entities-> GetComponent<PositionComp>(entity, ComponentType::Position);
            std::shared_ptr<DrawableComponent> drawable = nullptr;

            if (entities->HasComponent(entity, ComponentType::SpriteSheet))
            {
                drawable = entities-> GetComponent<DrawableComponent>(entity, ComponentType::SpriteSheet);
            } 
            else 
            { 
                continue; 
            }

            drawable->UpdatePosition(position->get_position());
        }
    }

    void RendererSystem::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event)
    {
        if (l_event == EntityEvent::Moving_Left ||
            l_event == EntityEvent::Moving_Right ||
            l_event == EntityEvent::Moving_Up ||
            l_event == EntityEvent::Moving_Down ||
            l_event == EntityEvent::Elevation_Change ||
            l_event == EntityEvent::Spawned)
        {
            SortDrawables();
        }
    }

    void RendererSystem::Notify(const Message& l_message)
    {
        if(HasEntity(l_message.m_receiver))
        {
            EntityMessage m = (EntityMessage)l_message.m_type;
            switch(m)
            {
                case EntityMessage::Direction_Changed:
                SetSheetDirection(l_message.m_receiver, static_cast<Direction>(std::get<int>(l_message.m_info)));
                break;
            }
        }
    }

    void RendererSystem::SetSheetDirection(const EntityId l_entity, const Direction l_dir)
    {
        auto entities = m_system_manager->GetEntityManager();

        if (!entities->HasComponent(l_entity, ComponentType::SpriteSheet))
        {
            return;
        }

        std::shared_ptr<SpriteSheetComponent> sheet = entities-> GetComponent<SpriteSheetComponent>(l_entity,ComponentType::SpriteSheet);
        sheet->GetSpriteSheet()->SetDirection(l_dir);
    }

    void RendererSystem::SortDrawables()
    {
        auto e_mgr = m_system_manager->GetEntityManager();

        std::sort(m_entities.begin(), m_entities.end(),[e_mgr](unsigned int l_1, unsigned int l_2)
        {
            auto pos1 = e_mgr->GetComponent<PositionComp>(l_1, ComponentType::Position);
            auto pos2 = e_mgr->GetComponent<PositionComp>(l_2, ComponentType::Position);

            if (pos1->get_elevation() == pos2->get_elevation())
            {
                return pos1->get_position().y < pos2->get_position().y;
            }

            return pos1->get_elevation() < pos2->get_elevation();
        });
    }
} // namespace Engine
