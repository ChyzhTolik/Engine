#include "Animation.hpp"

namespace Engine
{
    Animation::Animation(std::shared_ptr<sf::Texture> texture) : m_texture(texture)
    {
    }

    Animation::~Animation()
    {
    }

    void Animation::setTexture(TexturePtr texture)
    {
        m_texture = texture;
    }

    TexturePtr Animation::getTexture() const
    {
        return m_texture;
    }

    size_t Animation::size() const
    {
        return m_frames.size();
    }

    Animation& Animation::addFrame(const sf::IntRect& rect)
    {
        m_frames.emplace_back(rect);
        return *this;
    }

    Animation& Animation::addFramesLine(int number_x,int number_y,int line)
    {
        const sf::Vector2u size = m_texture->getSize();
        const float delta_x = size.x / float(number_x);
        const float delta_y = size.y / float(number_y);

        for(int i = 0;i<number_x;++i)
        {
            addFrame(sf::IntRect(i*delta_x,line*delta_y,delta_x,delta_y));
        }
        
        return *this;
    }

    Animation& Animation::addFramesColumn(int number_x,int number_y,int column)
    {
        const sf::Vector2u size = m_texture->getSize();
        const float delta_x = size.x / float(number_x);
        const float delta_y = size.y / float(number_y);
        
        for(int i = 0;i<number_y;++i)
        {
            addFrame(sf::IntRect(column*delta_x,i*delta_y,delta_x,delta_y));
        }

        return *this;
    }
} // namespace Engine
