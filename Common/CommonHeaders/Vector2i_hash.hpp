#pragma once

#include <SFML/System.hpp>

namespace Common
{
    struct Vector2i_hash 
    {
        size_t operator()(const sf::Vector2i& p) const
        {
            auto hash1 = std::hash<unsigned int>{}(p.x);
            auto hash2 = std::hash<unsigned int>{}(p.y);
    
            if (hash1 != hash2) {
                return hash1 ^ hash2;             
            }
            
            // If hash1 == hash2, their XOR is zero.
            return hash1;
        }
    };
} // namespace Common
