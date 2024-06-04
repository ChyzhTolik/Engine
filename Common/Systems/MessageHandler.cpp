#include "MessageHandler.hpp"

namespace Engine
{
    MessageHandler::MessageHandler(/* args */)
    {
    }
    
    MessageHandler::~MessageHandler()
    {
    }

    bool MessageHandler::subscribe(EntityMessage message_type, std::shared_ptr<Observer> observer)
    {
        return m_communicators.at(message_type).add_observer(observer);
    }

    bool MessageHandler::unsubscribe(EntityMessage message_type, std::shared_ptr<Observer> observer)
    {
        return m_communicators.at(message_type).remove_observer(observer);
    }

    void MessageHandler::dispatch(const Message& message)
    {
        auto itr = m_communicators.find(message.m_type);

        if (itr == m_communicators.end())
        {
            return;
        }
        
        itr->second.broadcast(message);
    }

} // namespace Engine
