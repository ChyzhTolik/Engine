#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "RendererSystem.hpp"

namespace Engine
{
    SystemManager::SystemManager() : m_entityManager(std::make_shared<EntitiesManager>(nullptr))
    {
    }
    
    SystemManager::~SystemManager()
    {
        PurgeSystems();
    }

    void SystemManager::SetEntityManager(std::shared_ptr<EntitiesManager> l_entityMgr)
    {
        m_entityManager = l_entityMgr;
    }

    std::shared_ptr<EntitiesManager> SystemManager::GetEntityManager()
    {
        return m_entityManager;
    }

    MessageHandler& SystemManager::GetMessageHandler()
    {
        return m_messages;
    }

    void SystemManager::AddEvent(const EntityId& l_entity, const EventID& l_event)
    {
        m_events[l_entity].AddEvent(l_event);
    }

    void SystemManager::Update(float l_dT)
    {
        for(auto &itr : m_systems)
        {
            itr.second->Update(l_dT);
        }

        HandleEvents();
    }

    void SystemManager::HandleEvents()
    {
        for(auto &event : m_events)
        {
            EventID id = 0;

            while(event.second.ProcessEvents(id))
            {
                for(auto &system : m_systems)
                {
                    if(system.second->HasEntity(event.first))
                    {
                        system.second->HandleEvent(event.first,(EntityEvent)id);
                    }
                }
            }
        }
    }

    void SystemManager::Draw(std::shared_ptr<Window> l_wind, unsigned int l_elevation)
    {
        auto itr = m_systems.find(SystemType::Renderer);

        if (itr == m_systems.end())
        { 
            return; 
        }

        std::shared_ptr<RendererSystem> system = std::dynamic_pointer_cast<RendererSystem>(itr->second);

        system->Render(l_wind, l_elevation);
    }

    void SystemManager::EntityModified(const EntityId& l_entity, const std::bitset<REQUIREMENTS_NUM>& l_bits)
    {
        for(auto &s_itr : m_systems)
        {
            std::shared_ptr<System> system = s_itr.second;

            if(system->FitsRequirements(l_bits))
            {
                if(!system->HasEntity(l_entity))
                {
                    system->AddEntity(l_entity);
                }
            } 
            else 
            {
                if(system->HasEntity(l_entity))
                {
                    system->RemoveEntity(l_entity);
                }
            }
        }
    }

    void SystemManager::RemoveEntity(const EntityId& l_entity)
    {
        for(auto &system : m_systems)
        {
            system.second->RemoveEntity(l_entity);
        }
    }

    void SystemManager::PurgeEntities()
    {
        for(auto &system : m_systems)
        {
            system.second->Purge();
        }
    }

    void SystemManager::PurgeSystems()
    {
        m_systems.clear();
    }
} // namespace Engine
