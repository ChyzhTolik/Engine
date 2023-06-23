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

        void set_texture(TexturePtr texture);
        TexturePtr get_texture() const;
        Animation& add_frame(const sf::IntRect& rect);

        // Divide a texture on number_x lines and number_y columns and add frames from the line_num line
        Animation& add_frames_line(int number_x,int number_y,int line_num);
        Animation& add_frames_column(int number_x,int number_y,int column);
        size_t size()const;
        const sf::IntRect& get_rect(size_t index)const;
    };
} // namespace Engine
