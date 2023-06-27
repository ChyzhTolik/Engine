#include "Animation.hpp"

namespace Engine
{
    Animation::Animation(TexturePtr texture) : m_texture(texture)
    {
    }

    Animation::~Animation()
    {
    }

    void Animation::set_texture(TexturePtr texture)
    {
        m_texture = texture;
    }

    TexturePtr Animation::get_texture() const
    {
        return m_texture;
    }

    size_t Animation::size() const
    {
        return m_frames.size();
    }

    Animation& Animation::add_frame(const sf::IntRect& rect)
    {
        m_frames.emplace_back(rect);
        return *this;
    }

    Animation& Animation::add_frames_line(int number_x,int number_y,int line_num)
    {
        const sf::Vector2u size = m_texture->getSize();
        const int delta_x = size.x / number_x;
        const int delta_y = size.y / number_y;

        for(int i = 0;i<number_x;++i)
        {
            add_frame(sf::IntRect({i*delta_x,line_num*delta_y},
                {delta_x,delta_y}));
        }

        return *this;
    }

    Animation& Animation::add_frames_column(int number_x,int number_y,int column)
    {
        const sf::Vector2u size = m_texture->getSize();
        const int delta_x = size.x / number_x;
        const int delta_y = size.y / number_y;
        
        for(int i = 0;i<number_y;++i)
        {
            add_frame(sf::IntRect({column*delta_x,i*delta_y},{delta_x,delta_y}));
        }

        return *this;
    }

    const sf::IntRect& Animation::get_rect(size_t index) const
    {
        return m_frames.at(index);
    }
} // namespace Engine
