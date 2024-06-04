#include "EventQueue.hpp"

namespace Engine
{
    EventQueue::EventQueue(/* args */)
    {
    }
    
    EventQueue::~EventQueue()
    {
    }

    void EventQueue::add_event(EntityEvent event)
    {
        m_queue.push(event);
    }

    bool EventQueue::process_event(EntityEvent& event)
    {
        if (m_queue.empty())
        {
            return false;
        }
        
        event = m_queue.front();
        m_queue.pop();

        return true;
    }

    void EventQueue::clear()
    {
        while (!m_queue.empty())
        {
            m_queue.pop();
        }
        
    }
} // namespace Engine
