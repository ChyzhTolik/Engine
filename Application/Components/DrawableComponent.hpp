#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace Engine
{
    class DrawableComponent : public Component
    {
    public:
        DrawableComponent(const ComponentType& l_type);
        virtual ~DrawableComponent();
        virtual void UpdatePosition(const sf::Vector2f& l_vec) = 0;
        virtual const sf::Vector2i GetSize() = 0;
        virtual void Draw(sf::RenderWindow& l_wind) = 0;
    };    
} // namespace Engine
