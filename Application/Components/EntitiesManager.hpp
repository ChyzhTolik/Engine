#pragma once

#include "Component.hpp"
#include <memory>
#include <vector>
#include <bitset>
#include <unordered_map>

namespace Engine
{
    const uint32_t ComponentsNumber = 20;
    using EntityId = uint32_t;

    class ComponentCreator
    {
    public:
        ComponentCreator(ComponentType type) : m_type(type){}
        virtual std::unique_ptr<Component> create() = 0;

    protected:
        ComponentType m_type;
    };

    class PositionCompCreator : public ComponentCreator
    {
    public:
        PositionCompCreator(ComponentType type);
        std::unique_ptr<Component> create() override;
    };

    using ComponentContainer = std::vector<std::shared_ptr<Component>>;
    using EntityData = std::pair<std::bitset<ComponentsNumber>,ComponentContainer>;
    using EntitiesContainer = std::unordered_map<EntityId,EntityData>;
    using ComponentFactory = std::unordered_map<ComponentType,std::unique_ptr<ComponentCreator>>;

    class SystemManager;

    class EntitiesManager
    {
    public:
        EntitiesManager(std::shared_ptr<SystemManager> system_manager);
        ~EntitiesManager();

        int AddEntity(const std::bitset<ComponentsNumber>& l_mask);
        int AddEntity(const std::string& l_entityFile);
        bool RemoveEntity(const EntityId& l_id);
        bool AddComponent(const EntityId& l_entity,const ComponentType& l_component);

        template<class T>
        std::shared_ptr<T> GetComponent(const EntityId& l_entity, const ComponentType& l_component);
        bool RemoveComponent(const EntityId& l_entity, const ComponentType& l_component);
        bool HasComponent(const EntityId& l_entity, const ComponentType& l_component);
        void Purge();
    private:
        template<typename T, typename ...Args> // T inherits from ComponentCreator
        void add_component_type(ComponentType l_type, Args&& ... args)
        {
            m_component_factory.insert({l_type, std::make_unique<T>(l_type, std::forward<Args>(args)...)});
        }

        std::shared_ptr<SystemManager> m_system_manager;
        unsigned int m_idCounter;
        EntitiesContainer m_entities;
        ComponentFactory m_component_factory;
    };

    template<class T>
    std::shared_ptr<T> EntitiesManager::GetComponent(const EntityId& l_entity, const ComponentType& l_component)
    {
        auto itr = m_entities.find(l_entity);

        if (itr == m_entities.end())
        { 
            return nullptr; 
        }
        // Found the entity.

        if (!itr->second.first[static_cast<u_int32_t>(l_component)])
        {
            return nullptr;
        }
        // Component exists.

        auto& container = itr->second.second;
        auto component = std::find_if(container.begin(),container.end(),
        [&l_component](std::shared_ptr<Component> c){
            return c->get_type() == l_component;
        });

        return (component != container.end() ? std::dynamic_pointer_cast<T>(*component) : nullptr);
    }
    
} // namespace Engine
