#include "Communicator.hpp"

#include <algorithm>

namespace Engine
{
    Communicator::Communicator(/* args */)
    {
    }
    
    Communicator::~Communicator()
    {
    }

    bool Communicator::add_observer(std::shared_ptr<Observer> observer)
    {
        if (has_observer(observer))
        {
            return false;
        }

        m_observers.emplace_back(observer);

        return true;
    }

    bool Communicator::remove_observer(std::shared_ptr<Observer> observer)
    {
        auto observer_itr = std::find_if(m_observers.begin(),m_observers.end(), [&observer](std::shared_ptr<Observer>& o)
        {
            return o == observer; 
        });

        if (observer_itr == m_observers.end())
        { 
            return false; 
        }

        m_observers.erase(observer_itr);
        return true;
    }
    
    bool Communicator::has_observer(std::shared_ptr<Observer> observer)
    {
        return (std::find_if(m_observers.begin(), m_observers.end(),[&observer](std::shared_ptr<Observer>& o)
        {
            return o == observer;
        }) != m_observers.end());
    }

    void Communicator::broadcast(Message message)
    {
        for (auto &&itr : m_observers)
        {
            itr->notify(message);
        }
    }
} // namespace Engine
