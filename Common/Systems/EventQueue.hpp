#pragma once

#include <queue>
#include <cstdint>
#include "EntityEvent.hpp"

namespace Engine
{
    class EventQueue
    {
    public:
        EventQueue(/* args */);
        ~EventQueue();

        void add_event(EntityEvent event);
        bool process_event(EntityEvent& event);
        void clear();
    private:
        std::queue<EntityEvent> m_queue;
    };
    
    
    
} // namespace Engine
