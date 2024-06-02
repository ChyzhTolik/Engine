#include "EntitiesManager.hpp"

#include "PositionComponent.hpp"
#include "MovableComponent.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Engine
{
    const std::vector<std::string> EntitiesManager::m_component_names
    {
        "Position",
        "SpriteSheet",
        "State",
        "Movable",
        "Controller",
        "Collidable",
    };

    EntitiesManager::EntitiesManager(std::shared_ptr<SystemManager> system_manager) : m_system_manager(system_manager), m_counter{0}
    {
        add_component_creator<PositionComponentCreator>(ComponentType::Position);
        add_component_creator<MovableComponentCreator>(ComponentType::Movable);
    }
    
    EntitiesManager::~EntitiesManager()
    {
    }

    uint32_t EntitiesManager::add_entity(ComponentBitSet mask)
    {
        EntityId entity_id = m_counter;

        if (!m_entities_map.emplace(entity_id,std::pair<ComponentBitSet,ComponentContainer>(0,ComponentContainer())).second)
        {
            return -1; 
        }

        ++m_counter;

        for(unsigned int i = 0; i < static_cast<size_t>(ComponentType::All); ++i)
        {
            if(mask.test(i) == 1)
            {
                add_component(entity_id,ComponentType(i)); 
            }
        }
        // Notifying the system manager of a modified entity.
        // m_system_manager->EntityModified(entity,l_mask);
        // m_system_manager->AddEvent(entity,(EventID)EntityEvent::Spawned);
        return entity_id;
    }

    bool EntitiesManager::add_component(EntityId id, ComponentType component_type)
    {
        bool result = false;
        auto itr = m_entities_map.find(id);

        if (itr == m_entities_map.end())
        { 
            return false; 
        }

        if (itr->second.first.test(static_cast<size_t>(component_type)))
        {
            return false;
        }

        // Component doesn't exist.
        auto itr2 = m_component_factory.find(component_type);

        if (itr2 == m_component_factory.end())
        { 
            return false; 
        }

        std::shared_ptr<Component> component = itr2->second->create();
        itr->second.second.emplace_back(component);
        itr->second.first.set(static_cast<size_t>(component_type));
        result = true;
        // Notifying the system manager of a modified entity.
        // m_systems->EntityModified(l_entity,itr->second.first);
        return result;
    }

    bool EntitiesManager::has_component(EntityId id, ComponentType component_type) const
    {
        bool result = false;
        auto itr = m_entities_map.find(id);

        if (itr == m_entities_map.end())
        { 
            return false; 
        }

        if (itr->second.first.test(static_cast<size_t>(component_type)))
        {
            result = true;
        }
        
        return result;
    }

    bool EntitiesManager::remove_component(EntityId id, ComponentType component_type)
    {
        bool result = false;
        auto itr = m_entities_map.find(id);

        if (itr == m_entities_map.end())
        { 
            return false; 
        }

        if (!itr->second.first.test(static_cast<size_t>(component_type)))
        {
            return false;
        }

        // Component exists.
        
        auto& container = itr->second.second;

        auto component = std::find_if(container.begin(),container.end(),
        [&component_type](std::shared_ptr<Component> c)
        {
            return c->get_type() == component_type;
        });

        if (component == container.end())
        {
            return false;
        }
        
        container.erase(component);
        itr->second.first.reset(static_cast<size_t>(component_type));

        result = true;
        // Notifying the system manager of a modified entity.
        // m_systems->EntityModified(l_entity,itr->second.first);
        return result;
    }

    bool EntitiesManager::remove_entity(EntityId id)
    {
        bool result = false;
        auto itr = m_entities_map.find(id);

        if (itr == m_entities_map.end())
        {
            return false; 
        }

        m_entities_map.erase(itr);
        result = true;

        return result;
    }

    size_t EntitiesManager::count() const
    {
        return m_entities_map.size();
    }

    void EntitiesManager::clear()
    {
        m_entities_map.clear();
    }

    void to_json(json& j, const EntityInfo& p) 
    {
        j=json{
            {"name", p.name},
            {"components", p.components}
        };
    }

    void from_json(const json& j, EntityInfo& p) 
    {
        j.at("name").get_to(p.name);

        j.at("components").get_to(p.components);
    }

    EntityId EntitiesManager::add_entity(std::string_view file_name)
    {
        EntityId entity_id;
        std::fstream map_file{static_cast<std::string>(file_name)};

        if (!map_file.good())
        { 
            std::cout << "! Failed loading " << file_name << "." << std::endl; 
            return -1; 
        }

        json jf = json::parse(map_file);

        EntityInfo entity_info = jf.at("EntityInfo");
        std::reverse(entity_info.components.begin(),entity_info.components.end());
        ComponentBitSet mask{entity_info.components};
        entity_id = add_entity(mask);

        for (size_t i = 0; i < static_cast<size_t>(ComponentType::All); i++)
        {
            if (mask.test(i))
            {
                auto component = std::find_if(
                    m_entities_map.at(entity_id).second.begin(), 
                    m_entities_map.at(entity_id).second.end(), 
                    [&i](const std::shared_ptr<Component>& comp)
                    {
                        return comp->get_type() == static_cast<ComponentType>(i);
                    }
                );

                if (component == m_entities_map.at(entity_id).second.end())
                {
                    continue;
                }

                auto comp = *component;
                comp->read_in(jf.at(m_component_names[i]));
            }
        }

        return entity_id;
    }
} // namespace Engine
