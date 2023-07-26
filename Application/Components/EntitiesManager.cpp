#include "EntitiesManager.hpp"

#include "PositionComp.hpp"
#include "SystemManager.hpp"

namespace Engine
{
    EntitiesManager::EntitiesManager(std::shared_ptr<SystemManager> system_manager) : m_system_manager(system_manager)
    {
        add_component_type<PositionCompCreator>(ComponentType::Position);
    }
    
    EntitiesManager::~EntitiesManager()
    {
    }

    PositionCompCreator::PositionCompCreator(ComponentType type) : ComponentCreator(type)
    {
        
    }

    std::unique_ptr<Component> PositionCompCreator::create()
    {
        return std::make_unique<PositionComp>(m_type);
    }

    int EntitiesManager::AddEntity(const std::bitset<ComponentsNumber>& l_mask)
    {
        EntityId entity = m_idCounter;

        if (!m_entities.emplace(entity,EntityData(0,ComponentContainer())).second)
        { 
            return -1; 
        }

        ++m_idCounter;

        for(unsigned int i = 0; i < ComponentsNumber; ++i)
        {
            if(l_mask[i] == 1)
            { 
                AddComponent(entity,ComponentType(i)); 
            }
        }
        // Notifying the system manager of a modified entity.
        m_system_manager->EntityModified(entity,l_mask);
        m_system_manager->AddEvent(entity,(EventID)EntityEvent::Spawned);
        return entity;
    }

    bool EntitiesManager::RemoveEntity(const EntityId& l_entity)
    {
        auto itr = m_entities.find(l_entity);

        if (itr == m_entities.end())
        { 
            return false; 
        }

        // Removing all components.
        while(itr->second.second.begin() != itr->second.second.end())
        {
            itr->second.second.pop_back();
        }

        m_entities.erase(itr);
        m_system_manager->RemoveEntity(l_entity);
        return true;
    }

    bool EntitiesManager::AddComponent(const EntityId& l_entity,const ComponentType& l_component)
    {
        auto itr = m_entities.find(l_entity);
        if (itr == m_entities.end())
        { 
            return false; 
        }

        if (itr->second.first[(unsigned int)l_component] == 1)
        {
            return false;
        }

        // Component doesn't exist.
        auto itr2 = m_component_factory.find(l_component);

        if (itr2 == m_component_factory.end())
        { 
            return false; 
        }

        // Component type does exist.
        std::shared_ptr<Component> component = itr2->second->create();
        itr->second.second.emplace_back(component);
        itr->second.first.set((unsigned int)l_component);
        // Notifying the system manager of a modified entity.
        m_system_manager->EntityModified(l_entity,itr->second.first);
        return true;
    }

    bool EntitiesManager::RemoveComponent(const EntityId& l_entity, const ComponentType& l_component)
    {
        auto itr = m_entities.find(l_entity);

        if (itr == m_entities.end())
        { 
            return false; 
        }

        // Found the entity.
        if (itr->second.first[(unsigned int)l_component] == 0)
        {
            return false;
        }

        // Component exists.
        auto& container = itr->second.second;
        auto component = std::find_if(container.begin(),container.end(),
        [&l_component](std::shared_ptr<Component> c)
        {
            return c->get_type() == l_component;
        });

        if (component == container.end())
        { 
            return false; 
        }
        
        container.erase(component);
        itr->second.first.reset((unsigned int)l_component);
        m_system_manager->EntityModified(l_entity, itr->second.first);
        return true;
    }

    bool EntitiesManager::HasComponent(const EntityId& l_entity, const ComponentType& l_component)
    {
        auto itr = m_entities.find(l_entity);

        if (itr == m_entities.end())
        { 
            return false; 
        }

        return itr->second.first[(unsigned int)l_component] == 1;
    }

    void EntitiesManager::Purge()
    {
        m_system_manager->PurgeEntities();
        for(auto& entity : m_entities)
        {
            entity.second.second.clear();
            entity.second.first.reset();
        }
        m_entities.clear();
        m_idCounter = 0;
    }

    int EntitiesManager::AddEntity(const std::string& l_entityFile)
    {
        return 0;
    }

} // namespace Engine
