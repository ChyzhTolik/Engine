#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
    class AnimatedSprite : public sf::Drawable, public sf::Transformable
    {
    private:
        /* data */
    public:
        AnimatedSprite(/* args */);
        ~AnimatedSprite();
    };
    
    AnimatedSprite::AnimatedSprite(/* args */)
    {
    }
    
    AnimatedSprite::~AnimatedSprite()
    {
    }
    
} // namespace Engine
