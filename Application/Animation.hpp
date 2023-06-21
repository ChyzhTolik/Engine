#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Engine
{
    using TexturePtr = std::shared_ptr<sf::Texture>;

    class Animation
    {
    private:
        friend class AnimatedSprite;
        std::vector<sf::IntRect> m_frames;
        TexturePtr m_texture;

    public:
        Animation(TexturePtr texture = nullptr);
        ~Animation();

        void setTexture(TexturePtr texture);
        TexturePtr getTexture() const;
        Animation& addFrame(const sf::IntRect& rect);
        Animation& addFramesLine(int number_x,int number_y,int line);
        Animation& addFramesColumn(int number_x,int number_y,int column);
        size_t size()const;
        const sf::IntRect& getRect(size_t index)const;
    };
} // namespace Engine
