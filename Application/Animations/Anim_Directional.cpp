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

        // if (direction == Direction::Left)
        // {
        //     std::cout<<"Left"<<std::endl;
        //     std::cout<<rect.left<<" "<<rect.top<<std::endl;
        //     std::cout<<"Invert"<<std::endl;
        //     auto inv_rect = invert_horizontal(rect);
        //     std::cout<<inv_rect.left<<" "<<inv_rect.top<<std::endl;
        // }        

        m_spriteSheet.CropSprite(m_spriteSheet.GetDirection() == Direction::Right ? rects[m_frameCurrent] : invert_horizontal(rects[m_frameCurrent]));
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
