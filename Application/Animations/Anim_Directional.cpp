#include "Anim_Directional.hpp"
#include "Anim_Directional.hpp"
#include "SpriteSheet.hpp"
#include <iostream>

namespace Engine
{
    void Anim_Directional::CropSprite()
    {
        sf::IntRect& rect = rects[m_frameCurrent];
        Direction direction = m_spriteSheet.GetDirection();    

        m_spriteSheet.CropSprite(m_spriteSheet.GetDirection() == Direction::Right ? rects[m_frameCurrent] : invert_horizontal(rects[m_frameCurrent]));

        if (!origins.empty())
        {
            sf::Vector2f origin = {origins[m_frameCurrent], 0.f};

            if (m_spriteSheet.GetDirection() == Direction::Right)
            {
                m_spriteSheet.set_sprite_origin(origin);
            }
            else
            {
                sf::Vector2f left_origin = {abs(rects[m_frameCurrent].width)-origin.x, 0.f};
                m_spriteSheet.set_sprite_origin(left_origin);
            }
        }
        
    }

    void Anim_Directional::FrameStep()
    {
        if(m_frameStart == m_frameEnd)
        {
            return;
        }

        if (m_frameStart < m_frameEnd)
        { 
            ++m_frameCurrent; 
        }
        else 
        { 
            --m_frameCurrent; 
        }

        if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd)||
        (m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
        {
            if (m_loop)
            { 
                m_frameCurrent = m_frameStart; 
                return; 
            }

            m_frameCurrent = m_frameEnd;
            Pause();
        }
    }

    sf::IntRect Anim_Directional::invert_horizontal(const sf::IntRect& rect)
    {
        sf::IntRect result = rect;
        result.left = rect.left + rect.width;
        result.width = -rect.width;

		return result;
    }
} // namespace Engine
