#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>
#include "Anim_Base.hpp"

namespace Engine
{
    enum class AnimationType
    {
        Idle,
        Running,
        Throwint,
        Firing,
        Siting,
        SitFiring,
        Jumping,
        JumpFiring,
        Death,
        Climbing,
    };

    struct FrameInfo
    {
        AnimationType type;
        float frame_time;
        std::vector<std::vector<int>> rects;
        int start_frame;
        int end_frame;
    };

    enum class Direction{ Right = 0, Left };

    using Animations = std::unordered_map<AnimationType,std::shared_ptr<Anim_Base>>;

    class SpriteSheet
    {
    public:
        SpriteSheet();
        ~SpriteSheet();
        void CropSprite(const sf::IntRect& l_rect);
        bool LoadSheet(const std::string& l_file);
        std::shared_ptr<Anim_Base> GetCurrentAnim();
        bool SetAnimation(AnimationType l_name, const bool& l_play = false, const bool& l_loop = false);
        void Update(const float& l_dT);
        void Draw(sf::RenderWindow& l_wnd);

        void SetSpriteSize(const sf::Vector2i& l_size);
        void SetSpritePosition(const sf::Vector2f& l_pos);
        void SetDirection(const Direction& l_dir);
        void SetSpriteScale(const sf::Vector2f& scale);

	    Direction GetDirection()const;
        sf::Vector2i GetSpriteSize()const;
        sf::Vector2f GetSpritePosition()const;

    private:
        std::string m_texture;
        sf::Sprite m_sprite;
        sf::Vector2i m_spriteSize;
        sf::Vector2f m_spriteScale;
        Direction m_direction;
        std::string m_animType;
        Animations m_animations;
        std::shared_ptr<Anim_Base> m_animationCurrent;
    };
    
} // namespace Engine
