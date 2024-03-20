#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
    class Tile
    {
    public:
        virtual ~Tile(){};

        virtual sf::Vector2f get_friction() const = 0;
        virtual void set_friction(const sf::Vector2f& friction) = 0;
        virtual sf::Vector2i get_size() const = 0;
        virtual bool is_deadly() const = 0;
    };    
} // namespace Engine
