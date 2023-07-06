#include "Anim_Directional.hpp"
#include "Anim_Directional.hpp"
#include "SpriteSheet.hpp"

namespace Engine
{
    void Anim_Directional::CropSprite()
    {
        m_spriteSheet->CropSprite(m_spriteSheet->GetDirection() == Direction::Right ? rects[m_frameCurrent] : invert_horizontal(rects[m_frameCurrent]));
    }

    void Anim_Directional::FrameStep()
    {
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
        sf::IntRect result;
        result.left = rect.left + rect.width;
        result.width = -rect.width;

		return result;
    }
} // namespace Engine
