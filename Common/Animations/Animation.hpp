#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Engine
{
    using TexturePtr = std::shared_ptr<sf::Texture>;

    class Animation
    {
    public:
        explicit Animation(const sf::Vector2u& texture_size);
        virtual ~Animation();
        Animation() = delete;

        Animation& add_frame(const sf::IntRect& rect);

        // Divide a texture_siae on number_x lines and number_y columns and add frames from the line_num line
        Animation& add_frames_line(int number_x,int number_y,int line_num);
        // Divide a texture_siae on number_x lines and number_y columns and add frames from the column
        Animation& add_frames_column(int number_x,int number_y,int column);
        
        size_t size()const;
        const sf::IntRect& get_rect(size_t index)const;
        
    private:
        friend class AnimatedSprite;
        std::vector<sf::IntRect> m_frames;
        sf::Vector2u m_texture_size;
    };
} // namespace Engine
