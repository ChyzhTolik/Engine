#pragma once

#include "Observer.hpp"
#include <vector>
#include <memory>

namespace Engine
{
    class Communicator
    {
    public:
        Communicator(/* args */)= default;
        ~Communicator();

        bool add_observer(std::shared_ptr<Observer> observer);
        bool has_observer(std::shared_ptr<Observer> observer);
        bool remove_observer(std::shared_ptr<Observer> observer);
        void broadcast(Message message);
    private:
        std::vector<std::shared_ptr<Observer>> m_observers;
    };
    
    
    
} // namespace Engine
