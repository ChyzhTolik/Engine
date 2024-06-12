#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <SpriteSheet.hpp>

namespace Engine
{
    class DrawableComponentInterface : public Component
    {
    public:
        DrawableComponentInterface(ComponentType type) : Component(type) {}
        virtual ~DrawableComponentInterface(){}

        virtual void update_position(const sf::Vector2f& l_vec) = 0;
        virtual const sf::Vector2i get_size() = 0;
        virtual void draw(sf::RenderWindow& l_wind) = 0;
        virtual void update(float time) = 0;
        virtual std::shared_ptr<SpriteSheet> get_sprite_sheet() = 0;
    private:
    };
} // namespace Engine
