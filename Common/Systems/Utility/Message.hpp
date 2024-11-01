#pragma once

#include <cstdint>
#include <variant>
#include <SFML/Graphics.hpp>
#include "Enums/EntityMessage.hpp"
#include "Direction.hpp"
#include "EntityState.hpp"

namespace Engine
{
    using MessageId = uint32_t;

    struct Message
    {
        Message(EntityMessage type) : m_type{type}
        {
            
        }

        EntityMessage m_type;
        uint32_t m_sender;
        uint32_t m_receiver;

        std::variant<sf::Vector2f, bool, uint32_t, Direction, EntityState> m_data;
    };
    
    
} // namespace Engine
