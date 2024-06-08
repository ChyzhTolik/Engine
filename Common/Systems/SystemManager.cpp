#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "RendererSystem.hpp"
#include "MovementSystem.hpp"
#include "StateSystem.hpp"

namespace Engine
{
    SystemManager::SystemManager(/* args */) : m_entity_manager{nullptr}, m_message_handler{std::make_shared<MessageHandler>()}
    {

    }

    void SystemManager::fill_systems()
    {
        m_systems[SystemType::Renderer] = std::make_shared<RendererSystem>(shared_from_this());
        m_systems[SystemType::Movement] = std::make_shared<MovementSystem>(shared_from_this());
        m_systems[SystemType::State] = std::make_shared<StateSystem>(shared_from_this());

        for (auto &&system : m_systems)
        {
            system.second->subscribe();
        }
        
    }
    
    SystemManager::~SystemManager()
    {
        purge_systems();
    }

    void SystemManager::set_entity_manager(std::shared_ptr<EntitiesManager> entity_manager)
    {
        if (!m_entity_manager)
        {
            m_entity_manager = entity_manager;
        }        
    }

    std::shared_ptr<EntitiesManager> SystemManager::get_entity_manager()
    {
        return m_entity_manager;
    }

    std::shared_ptr<MessageHandler> SystemManager::get_message_handler()
    {
        return m_message_handler;
    }

    void SystemManager::add_event(const EntityId& entity, const EntityEvent& event)
    {
        m_events[entity].add_event(event);
    }

    void SystemManager::update(float time)
    {
        for (auto &&itr : m_systems)
        {
            itr.second->update(time);
        }

        handle_events();        
    }

    void SystemManager::handle_events()
    {
        for (auto &&event : m_events)
        {
            EntityEvent id = EntityEvent::Became_Idle;

            while (event.second.process_event(id))
            {
                for (auto &&system : m_systems)
                {
                    if (system.second->has_entity(event.first))
                    {
                        system.second->handle_event(event.first, id);
                    }
                }
            }
        }
    }

    void SystemManager::draw(std::shared_ptr<Window> window, u_int16_t elevation)
    {
        auto itr = m_systems.find(SystemType::Renderer);

        if (itr == m_systems.end())
        {
            return;
        }

        std::shared_ptr<RendererSystem> system_renderer = std::dynamic_pointer_cast<RendererSystem>(itr->second);
        system_renderer->render(window, elevation);
    }

    void SystemManager::entity_modified(EntityId entity, const ComponentBitSet& mask)
    {
        for (auto &&system_itr : m_systems)
        {
            auto system = system_itr.second;

            if (system->fits_requirements(mask))
            {
                if (!system->has_entity(entity))
                {
                    system->add_entity(entity);
                }                
            }
            else
            {
                if (system->has_entity(entity))
                {
                    system->remove_entity(entity);
                }
            }
        }
    }

    void SystemManager::remove_entity(const EntityId entity)
    {
        for (auto &&system : m_systems)
        {
            system.second->remove_entity(entity);
        }
    }

    void SystemManager::purge_entities()
    {
        for (auto &&system : m_systems)
        {
            system.second->purge();
        }
        
    }

    void SystemManager::purge_systems()
    {
        m_systems.clear();
    }
} // namespace Engine
