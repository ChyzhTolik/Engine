#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <memory>
#include <vector>

namespace Engine
{
    class SpriteSheet;

    template<typename T>
    class SpriteSheetTemplate;

    using Frame = unsigned int;

    class Anim_Base
    {
        friend class SpriteSheet;

        template<typename T>
        friend class SpriteSheetTemplate;
    public:
        Anim_Base(SpriteSheet& l_sprite_sheet);
        virtual ~Anim_Base();
        void Play();
        void Pause();
        void Stop();
        void Reset();
        bool is_playing() const;
        virtual void Update(const float& l_dT);
        void SetLooping(bool l_loop);
        void SetFrame(const unsigned int& l_frame);
        bool IsInAction();
        void SetRectangles(std::vector<sf::IntRect>&& rects);
        void SetStartFrame(Frame l_frame);
	    void SetEndFrame(Frame l_frame);
        sf::Vector2i get_current_sprite_size() const;
        size_t rects_count() const;
        bool is_attack() const;
        bool is_death() const;

    protected:        
        virtual void FrameStep() = 0;
        virtual void CropSprite() = 0;
        Frame m_frameCurrent;
        Frame m_frameStart;
        Frame m_frameEnd;
        std::vector<sf::IntRect> m_rects;
        std::vector<float> origins;
        int m_frameActionStart; // Frame when a specific "action" begins
        int m_frameActionEnd; // Frame when a specific "action" ends
        float m_frameTime;
        float m_elapsedTime;
        bool m_loop;
        bool m_playing;
        SpriteSheet& m_spriteSheet;
        bool m_is_attack{false};
        bool m_is_death{false};
    };
    
} // namespace Engine
