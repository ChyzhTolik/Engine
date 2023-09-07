#pragma once

#include "System.hpp"
#include "Window.hpp"
#include "EventQueue.hpp"
#include "MessageHandler.hpp"

namespace Engine
{
    class EntitiesManager;

    using SystemContainer = std::unordered_map<SystemType,std::shared_ptr<System>>;
    using EntityEventContainer = std::unordered_map<EntityId,EventQueue>;

    class SystemManager : std::enable_shared_from_this<SystemManager>
    {
    public:
        SystemManager();
        ~SystemManager();

        void SetEntityManager(std::shared_ptr<EntitiesManager> l_entityMgr);
        std::shared_ptr<EntitiesManager> GetEntityManager();
        MessageHandler& GetMessageHandler();
        template<class T>
        std::shared_ptr<T> GetSystem(const SystemType& l_system);
        void AddEvent(const EntityId& l_entity, const EventID& l_event);
        void Update(float l_dT);
        void HandleEvents();
        void Draw(std::shared_ptr<Window> l_wind, unsigned int l_elevation);
        void EntityModified(const EntityId& l_entity, const std::bitset<REQUIREMENTS_NUM>& l_bits);
        void RemoveEntity(const EntityId& l_entity);
        void PurgeEntities();
        void PurgeSystems();
    private:
        SystemContainer m_systems;
        std::shared_ptr<EntitiesManager> m_entityManager;
        EntityEventContainer m_events;
        MessageHandler m_messages;
    };
  
    template<class T>
    std::shared_ptr<T> SystemManager::GetSystem(const SystemType& l_system)
    {
        auto itr = m_systems.find(l_system);
        return(itr != m_systems.end() ? std::dynamic_pointer_cast<T>(itr->second) : nullptr);
    }
} // namespace Engine
