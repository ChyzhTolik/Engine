#pragma once

#include <memory>
#include <unordered_map>
#include <bitset>
#include <vector>

#include <Component.hpp>

namespace Engine
{
    using EntityId = uint32_t;
    using ComponentContainer = std::vector<std::shared_ptr<Component>>;
    using ComponentBitSet = std::bitset<static_cast<size_t>(ComponentType::All)>;

    struct EntityInfo
    {
        std::string name;
        std::string components;
    };

    class SystemManager
    {
        public:
        SystemManager(){}
    };

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

    private:

        template<typename T, typename ...Args>
        void add_component_creator(ComponentType l_type, Args&& ... args);

        std::shared_ptr<SystemManager> m_system_manager;
        uint32_t m_counter;
        std::unordered_map<EntityId,std::pair<ComponentBitSet,ComponentContainer>> m_entities_map;
        std::unordered_map<ComponentType, std::unique_ptr<ComponentCreator>> m_component_factory;
        static const std::vector<std::string> m_component_names;
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
        [&component_type](std::shared_ptr<Component> c)
        {
            return c->get_type() == component_type;
        });

        return (component != container.end() ? std::dynamic_pointer_cast<T>(*component) : nullptr);
    }
} // namespace Engine
