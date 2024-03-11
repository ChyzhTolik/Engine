#include "AnimatedSprite.hpp"

namespace Engine
{
    AnimatedSprite::FuncType AnimatedSprite::defaultFunc = []()->void{};

    AnimatedSprite::AnimatedSprite(
            const sf::Texture& texture,
            AnimationPtr animation,
            Status status,
            const sf::Time& deltaTime,
            bool loop,
            int repeat
        ) : sf::Sprite(texture),
        m_animation(animation),
        m_status(status),
        m_delta(deltaTime),
        m_loop(loop),
        m_repeat(repeat),
        m_current_frame(0)
    {
        set_animation(animation);
    }

    void AnimatedSprite::set_animation(AnimationPtr animation)
    {
        if(m_animation != animation)
        {
            m_animation = animation;
            m_elapsed = sf::Time::Zero;
            m_current_frame = 0;
            set_frame(0,true);
        }
    }

    AnimationPtr AnimatedSprite::get_animation()const
    {
        return m_animation;
    }

    void AnimatedSprite::set_frame_time(sf::Time deltaTime)
    {
        m_delta = deltaTime;
    }

    sf::Time AnimatedSprite::get_frame_time()const
    {
        return m_delta;
    }

    void AnimatedSprite::set_loop(bool loop)
    {
        m_loop = loop;
    }

    bool AnimatedSprite::get_loop() const
    {
        return m_loop;
    }

    void AnimatedSprite::set_repeat(int nb)
    {
        m_repeat = nb;
    }
    
    int AnimatedSprite::get_repeat()const
    {
        return m_repeat;
    }

    void AnimatedSprite::play()
    {
        m_status = Status::Playing;
    }

    void AnimatedSprite::pause()
    {
        m_status = Status::Paused;
    }

    void AnimatedSprite::stop()
    {
        m_status = Status::Stopped;
        m_current_frame = 0;
        set_frame(0,true);
    }

    AnimatedSprite::Status AnimatedSprite::get_status()const
    {
        return m_status;
    }

    void AnimatedSprite::set_frame(size_t index)
    {
        assert(m_animation);
        m_current_frame = index % m_animation->size();
        set_frame(m_current_frame,true);
    }

    void AnimatedSprite::set_color(const sf::Color& color)
    {
        m_vertices[0].color = color;
        m_vertices[1].color = color;
        m_vertices[2].color = color;
        m_vertices[3].color = color;
    }

    void AnimatedSprite::update(const sf::Time& deltaTime)
    {
        if (m_status == Status::Playing && m_animation)
        {
            m_elapsed += deltaTime;

            if (m_elapsed > m_delta)
            {
                m_elapsed -= m_delta;

                if (m_current_frame + 1 < m_animation->size())
                {
                    ++m_current_frame;
                }
                else
                {
                    m_current_frame = 0;

                    if (!m_loop)
                    {
                        --m_repeat;

                        if (m_repeat <= 0)
                        {
                            m_status = Status::Stopped;
                            on_finished();
                        }                        
                    }                    
                }                
            }

            set_frame(m_current_frame, false);            
        }        
    }

    void AnimatedSprite::set_frame(size_t index,bool resetTime)
    {
        if(m_animation)
        {
            sf::IntRect rect = m_animation->get_rect(index);
            setTextureRect(rect);
        }

        if(resetTime)
        {
            m_elapsed = sf::Time::Zero;
        }
    }
} // namespace Engine
