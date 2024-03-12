#pragma once

#include "SpriteSheet.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

using nlohmann::json;

namespace Engine
{
    template<typename T>
    struct FrameInfo
    {
        T type;
        float frame_time;
        std::vector<std::vector<int>> rects;
        std::vector<float> origins;
        int start_frame;
        int end_frame;
    };

    template<typename T>
    class SpriteSheetTemplate : public SpriteSheet
    {
    public:
        SpriteSheetTemplate(/* args */);
        ~SpriteSheetTemplate();
        T get_current_type() const;
        bool SetAnimation(T l_name, const bool& l_play = false, const bool& l_loop = false);

        template<class Animation>
        bool LoadSheet(const std::string& l_file, Configuration::Textures texture_id);
        void test_json();
    private:
        std::unordered_map<T,std::shared_ptr<Anim_Base>> m_animations;
        T m_current_type;

    };

    template<typename T>
    SpriteSheetTemplate<T>::SpriteSheetTemplate(/* args */)
    {
    }
    
    template<typename T>
    SpriteSheetTemplate<T>::~SpriteSheetTemplate()
    {
    }

    template<typename T>
    bool SpriteSheetTemplate<T>::SetAnimation(T l_name, const bool& l_play, const bool& l_loop)
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

        if(l_play)
        { 
            m_animationCurrent->Play(); 
        }
        
        m_animationCurrent->CropSprite();
        m_current_type = itr->first;

        return true;
    }
    
    template<typename T>
    void to_json(json& j, const FrameInfo<T>& p)
    {
        j=json{
            {"type", p.type},
            {"frame_time",p.frame_time},
            {"rects",p.rects},
            {"start_frame",p.start_frame},
            {"end_frame",p.end_frame},
            {"origins",p.origins},
        };
    }

    template<typename T>
    void from_json(const json& j, FrameInfo<T>& p)
    {
        j.at("type").get_to(p.type);
        j.at("frame_time").get_to(p.frame_time);
        j.at("rects").get_to(p.rects);
        j.at("start_frame").get_to(p.start_frame);
        j.at("end_frame").get_to(p.end_frame);
        j.at("origins").get_to(p.origins);
    }

    template<typename T>
    template<class Animation>
    bool SpriteSheetTemplate<T>::LoadSheet(const std::string& l_file, Configuration::Textures texture_id)
    {
        m_sprite = std::make_shared<sf::Sprite>(Configuration::textures.get(Configuration::Textures(texture_id)));
        std::ifstream frames;
        frames.open(l_file);

        if (!frames.is_open())
        {
            std::cout << "! Failed loading "<<l_file<<"." << std::endl; 
            return false; 
        }

	    json jf = json::parse(frames);
        std::vector<FrameInfo<T>> frame_infos;
        frame_infos = jf;

        for (auto &&frame : frame_infos)
        {
            std::shared_ptr<Anim_Base> animation = std::make_shared<Animation>(*this);
            animation->m_frameTime = frame.frame_time;
            animation->m_frameStart = frame.start_frame;
            animation->m_frameEnd = frame.end_frame;
            
            for (auto &&rect : frame.rects)
            {
                sf::IntRect frame_rect({rect[0],rect[1]},{rect[2]-rect[0],rect[3]-rect[1]});
                animation->m_rects.emplace_back(frame_rect);
            }

            for (auto &&origin : frame.origins)
            {
                animation->origins.push_back(origin);
            }            

            m_animations.emplace(T(frame.type),animation);

            if (m_animationCurrent)
            { 
                continue; 
            }

            SetAnimation(T(frame.type), true, true);
            m_animationCurrent = animation;
            m_animationCurrent->Play();
        }

        return true;
    }

    template<typename T>
    T SpriteSheetTemplate<T>::get_current_type() const
    {
        return m_current_type;
    }

    template<typename T>
    void SpriteSheetTemplate<T>::test_json()
    {
        
    }
} // namespace Engine
