#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
    class Background : public sf::Sprite
    {
    private:

    public:
        Background(const sf::Texture& texture);
        virtual ~Background();
    };  
} // namespace Engine
