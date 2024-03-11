#include "SpriteSheet.hpp"
#include "Anim_Directional.hpp"
#include "Configuration.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using nlohmann::json;

namespace Engine
{
    SpriteSheet::SpriteSheet() : m_animationCurrent(nullptr),
        m_spriteScale(1.f, 1.f), m_direction(Direction::Right)
    {
        
    }

    SpriteSheet::~SpriteSheet()
    {

    }

    void SpriteSheet::SetSpritePosition(const sf::Vector2f& l_pos)
    {
        m_sprite->setPosition(l_pos);
    }

    void SpriteSheet::SetDirection(const Direction& l_dir)
    {
        if (l_dir == m_direction)
        { 
            return; 
        }

        m_direction = l_dir;
        m_animationCurrent->CropSprite();
    }

    void SpriteSheet::CropSprite(const sf::IntRect& l_rect)
    {
        m_sprite->setTextureRect(l_rect);
    }

    void SpriteSheet::Update(const float& l_dT)
    {
        m_animationCurrent->Update(l_dT);
    }

    void SpriteSheet::Draw(sf::RenderWindow& l_wnd)
    {
        l_wnd.draw(*m_sprite);
    }

    sf::Vector2i SpriteSheet::GetSpriteSize()const
    {
        return m_animationCurrent->get_current_sprite_size();
    }
        
    sf::Vector2f SpriteSheet::GetSpritePosition()const
    {
        return m_sprite->getPosition();
    }

    Direction SpriteSheet::GetDirection()const
    {
        return m_direction;
    }

    std::shared_ptr<Anim_Base> SpriteSheet::GetCurrentAnim()
    {
        return m_animationCurrent;
    }

    void SpriteSheet::SetSpriteScale(const sf::Vector2f& scale)
    {
        m_sprite->setScale(scale);
    }

    void SpriteSheet::set_sprite_origin(const sf::Vector2f& l_origin)
    {
        m_sprite->setOrigin(l_origin);
    }

    sf::Vector2f SpriteSheet::get_origin()const
    {
        return m_sprite->getOrigin();
    }
} // namespace Engine
