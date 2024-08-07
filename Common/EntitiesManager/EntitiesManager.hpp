#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <Component.hpp>

namespace Engine
{
    using EntityId = uint32_t;
    using ComponentContainer = std::vector<std::shared_ptr<Component>>;    

    struct EntityInfo
    {
        std::string name;
        std::string components;
    };

    class SystemManager;

    class EntitiesManager
    {
    public:
        EntitiesManager(std::shared_ptr<SystemManager> system_manager);
        ~EntitiesManager();

        EntityId add_entity(ComponentBitSet mask);
        EntityId add_entity(std::string_view file_name);
        bool remove_entity(EntityId id);
        size_t count() const;

        bool add_component(EntityId id, ComponentType component_type);
        bool has_component(EntityId id, ComponentType component_type) const;
        bool remove_component(EntityId id, ComponentType component_type);

        template<class T>
        std::shared_ptr<T> get_component(EntityId id, ComponentType component_type);

        void clear();
        void set_player_id(const uint32_t id);
        uint32_t get_player_id() const;

    private:

        template<typename T, typename ...Args>
        void add_component_creator(ComponentType l_type, Args&& ... args);

        std::shared_ptr<SystemManager> m_system_manager;
        uint32_t m_counter;
        std::unordered_map<EntityId,std::pair<ComponentBitSet,ComponentContainer>> m_entities_map;
        std::unordered_map<ComponentType, std::unique_ptr<ComponentCreator>> m_component_factory;
        static const std::vector<std::string> m_component_names;
        uint32_t m_player_id;
    };

    template<typename T, typename ...Args>
    void EntitiesManager::add_component_creator(ComponentType l_type, Args&& ... args)
    {
        m_component_factory.insert({l_type, std::make_unique<T>(std::forward<Args>(args)...)});
    }

    template<class T>
    std::shared_ptr<T> EntitiesManager::get_component(EntityId id, ComponentType component_type)
    {
        auto itr = m_entities_map.find(id);

        if (itr == m_entities_map.end())
        { 
            return nullptr; 
        }

        if (!itr->second.first.test(static_cast<size_t>(component_type)))
        {
            return nullptr;
        }

        std::vector<std::shared_ptr<Component>>& container = itr->second.second;

        auto component = std::find_if(container.begin(),container.end(),
        [&component_type](const std::shared_ptr<Component>& c)
        {
            return c->get_type() == component_type;
        });

        if (component == container.end())
        {
            return nullptr;
        }
        
        std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(*component);
        return result;
    }
} // namespace Engine
