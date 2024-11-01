#pragma once

#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "System.hpp"
#include "Utility/EventQueue.hpp"
#include "Utility/MessageHandler.hpp"
#include "Window.hpp"
#include "InfoBox.hpp"
#include "spdlog/spdlog.h"

namespace Engine
{
    class EntitiesManager;

    class SystemManager : public std::enable_shared_from_this<SystemManager>
    {
    public:
        SystemManager(/* args */);
        ~SystemManager();

        void set_entity_manager(std::shared_ptr<EntitiesManager> entity_manager);
        void fill_systems();
        std::shared_ptr<EntitiesManager> get_entity_manager();
        std::shared_ptr<MessageHandler> get_message_handler();

        void add_event(const EntityId& entity, const EntityEvent& event);
        void update(float time);
        void draw(std::shared_ptr<Window> window, u_int16_t elevation);

        void entity_modified(EntityId entity, const ComponentBitSet& mask);
        void remove_entity(const EntityId entity);

        void purge_entities();
        void purge_systems();

        void set_infobox(std::shared_ptr<InfoBox> infobox);
        std::shared_ptr<InfoBox> get_infobox();

        void set_logger(std::shared_ptr<spdlog::logger> log_file);
        std::shared_ptr<spdlog::logger> get_logger();

        template<typename T>
        std::shared_ptr<T> get_system(SystemType system_type);
    private:
        void handle_events_async();
        void handle_events();

        std::unordered_map<SystemType, std::shared_ptr<System>> m_systems;
        std::shared_ptr<EntitiesManager> m_entity_manager;
        std::unordered_map<EntityId, EventQueue> m_event_queues;
        std::shared_ptr<MessageHandler> m_message_handler;
        std::shared_ptr<InfoBox> m_infobox;
        std::shared_ptr<spdlog::logger> m_log_file;

        std::thread m_event_handler_thread;
        std::condition_variable m_cond_var;
        std::mutex m_mutex;
        bool m_stop;
    };
    
    template<typename T>
    std::shared_ptr<T> SystemManager::get_system(SystemType system_type)
    {
        auto itr = m_systems.find(system_type);

        return(itr!=m_systems.end()?std::dynamic_pointer_cast<T>(itr->second):nullptr);
    }
    
} // namespace Engine
