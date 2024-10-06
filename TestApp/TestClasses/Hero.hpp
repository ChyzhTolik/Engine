#pragma once

#include "SFML/Graphics.hpp"
#include <string>

namespace Test
{
    class Hero
    {
    public:
        explicit Hero(const sf::Texture& texture);
        ~Hero();

        void init(const sf::Vector2f& position, const float mass);
        void update(float dt);
        void jump(float velocity);
        sf::Sprite& get_sprite();
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_position;
        uint8_t m_jump_count;
        float m_mass;
        float m_velocity;
        const float m_gravity = 9.8f;
        bool m_grounded;
    };
} // namespace Test
