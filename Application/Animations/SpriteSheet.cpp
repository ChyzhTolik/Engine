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
        m_spriteScale(1.f, 1.f), m_direction(Direction::Right), m_sprite(Configuration::textures.get(Configuration::Textures::Biomenace))
    {
        
    }

    SpriteSheet::~SpriteSheet()
    {

    }

    void SpriteSheet::SetSpriteSize(const sf::Vector2i& l_size)
    {
        m_spriteSize = l_size;
        m_sprite.setOrigin({m_spriteSize.x / 2.f, m_spriteSize.y / 1.f});
    }

    void SpriteSheet::SetSpritePosition(const sf::Vector2f& l_pos)
    {
        m_sprite.setPosition(l_pos);
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
        m_sprite.setTextureRect(l_rect);
    }

    bool SpriteSheet::SetAnimation(AnimationType l_name, const bool& l_play, const bool& l_loop)
    {
        auto itr = m_animations.find(l_name);

        if (itr == m_animations.end())
        { 
            return false; 
        }

        if (itr->second == m_animationCurrent)
        { 
            return false; 
        }

        if (m_animationCurrent)
        {
             m_animationCurrent->Stop(); 
        }
        
        m_animationCurrent = itr->second;
        m_animationCurrent->SetLooping(l_loop);
        if(l_play){ m_animationCurrent->Play(); }
        m_animationCurrent->CropSprite();

        return true;
    }

    void SpriteSheet::Update(const float& l_dT)
    {
        m_animationCurrent->Update(l_dT);
    }

    void SpriteSheet::Draw(sf::RenderWindow& l_wnd)
    {
        l_wnd.draw(m_sprite);
    }

    sf::Vector2i SpriteSheet::GetSpriteSize()const
    {
        return m_spriteSize;
    }
        
    sf::Vector2f SpriteSheet::GetSpritePosition()const
    {
        return m_sprite.getPosition();
    }

    Direction SpriteSheet::GetDirection()const
    {
        return m_direction;
    }

    void to_json(json& j, const FrameInfo& p)
    {
        j=json{
            {"type", p.type},
            {"frame_time",p.frame_time},
            {"rects",p.rects},
            {"start_frame",p.start_frame},
            {"end_frame",p.end_frame},
        };
    }

    void from_json(const json& j, FrameInfo& p)
    {
        j.at("type").get_to(p.type);
        j.at("frame_time").get_to(p.frame_time);
        j.at("rects").get_to(p.rects);
        j.at("start_frame").get_to(p.start_frame);
        j.at("end_frame").get_to(p.end_frame);
    }

    bool SpriteSheet::LoadSheet(const std::string& l_file)
    {
        std::ifstream frames;
        frames.open("media/Player.json");

        if (!frames.is_open())
        { 
            std::cout << "! Failed loading Player.json." << std::endl; 
            return false; 
        }

	    json jf = json::parse(frames);
        std::vector<FrameInfo> frame_infos;
        frame_infos = jf;

        for (auto &&frame : frame_infos)
        {
            std::shared_ptr<Anim_Base> animation = std::make_shared<Anim_Directional>();
            animation->m_frameTime = frame.frame_time;
            animation->m_frameStart = frame.start_frame;
            animation->m_frameEnd = frame.end_frame;
            
            for (auto &&rect : frame.rects)
            {
                sf::IntRect frame_rect({rect[0],rect[1]},{rect[2]-rect[0],rect[3]-rect[1]});
                animation->rects.emplace_back(frame_rect);
            }

            m_animations.emplace(AnimationType(frame.type),std::move(animation));            
        }        

        frames.close();
        return true;
    }
} // namespace Engine
