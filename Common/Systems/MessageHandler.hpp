#pragma once

#include <unordered_map>
#include "EntityMessage.hpp"
#include "Communicator.hpp"
#include <memory>

namespace Engine
{
    class MessageHandler
    {
    public:
        MessageHandler(/* args */);
        ~MessageHandler();

        bool subscribe(EntityMessage message_type, std::shared_ptr<Observer> observer);
        bool unsubscribe(EntityMessage message_type, std::shared_ptr<Observer> observer);
        void dispatch(const Message& message);
    private:
        std::unordered_map<EntityMessage,Communicator> m_communicators;
    };
    
    
    
} // namespace Engine
