#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>
#include "Anim_Base.hpp"
#include "Direction.hpp"

namespace Engine
{
    class SpriteSheet
    {
    public:
        virtual ~SpriteSheet();
        void CropSprite(const sf::IntRect& l_rect);
        std::shared_ptr<Anim_Base> GetCurrentAnim();
        void Update(const float& l_dT);
        void Draw(sf::RenderWindow& l_wnd);

        void SetSpritePosition(const sf::Vector2f& l_pos);
        void SetDirection(const Direction& l_dir);
        void SetSpriteScale(const sf::Vector2f& scale);
        void set_sprite_origin(const sf::Vector2f& l_origin);

	    Direction GetDirection()const;
        sf::Vector2i GetSpriteSize()const;
        sf::Vector2f GetSpritePosition()const;
        sf::Vector2f get_origin()const;

    protected:
        SpriteSheet();
        SpriteSheet(const SpriteSheet&){};
        SpriteSheet(const SpriteSheet&&){};
        std::shared_ptr<sf::Sprite> m_sprite;
        sf::Vector2f m_spriteScale;
        Direction m_direction;
        std::shared_ptr<Anim_Base> m_animationCurrent;

    private:
    };
    
} // namespace Engine
