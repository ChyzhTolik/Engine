#include "Anim_Base.hpp"
#include "SpriteSheet.hpp"

namespace Engine
{
    Anim_Base::Anim_Base(SpriteSheet& l_sprite_sheet): m_spriteSheet(l_sprite_sheet), m_frameCurrent(0), m_frameStart(0),
        m_frameEnd(0), m_frameTime(0.f),
        m_elapsedTime(0.f), m_frameActionStart(-1),
        m_frameActionEnd(-1), m_loop(false), m_playing(false)
    {

    }

    Anim_Base::~Anim_Base()
    {

    }

    void Anim_Base::SetFrame(const unsigned int& l_frame)
    {
        if((l_frame >= m_frameStart && l_frame <= m_frameEnd)||(l_frame >= m_frameEnd && l_frame <= m_frameStart))
        {
            m_frameCurrent = l_frame;
        }
    }

    bool Anim_Base::IsInAction()
    {
        if(m_frameActionStart == -1 || m_frameActionEnd == -1)
        {
            return true;
        }

        return (m_frameCurrent >= m_frameActionStart && m_frameCurrent <= m_frameActionEnd);
    }

    void Anim_Base::Play()
    { 
        m_playing = true; 
    }

    void Anim_Base::Pause()
    { 
        m_playing = false; 
    }

    void Anim_Base::Stop()
    { 
        m_playing = false; 
        Reset(); 
    }

    void Anim_Base::Reset()
    {
        m_frameCurrent = m_frameStart;
        m_elapsedTime = 0.0f;
        CropSprite();
    }

    void Anim_Base::Update(const float& l_dT)
    {
        if (!m_playing)
        { 
            return; 
        }

        m_elapsedTime += l_dT;

        if (m_elapsedTime < m_frameTime)
        { 
            return; 
        }

        FrameStep();
        CropSprite();
        m_elapsedTime = 0;
    }

    void Anim_Base::SetLooping(bool l_loop)
    { 
        m_loop = l_loop; 
    }

    void Anim_Base::SetStartFrame(Frame l_frame)
    {
        m_frameStart = l_frame;
    }

	void Anim_Base::SetEndFrame(Frame l_frame)
    {
        m_frameEnd = l_frame;
    }

    void Anim_Base::SetRectangles(std::vector<sf::IntRect>&& rects)
    {
        rects = std::move(rects);
    }

    bool Anim_Base::is_playing() const
    {
        return m_playing;
    }
    
    sf::Vector2i Anim_Base::get_current_sprite_size() const
    {
        return rects[m_frameCurrent].getSize();
    }

    std::string Anim_Base::get_name() const
    {
        return m_name;
    }


} // namespace Engine
