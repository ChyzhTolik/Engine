#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include "Direction.hpp"

namespace Engine
{
    class MovableComponent : public Component
    {
    public:
        MovableComponent();
        ~MovableComponent();
        void load(std::stringstream& l_stream) override;
        void add_velocity(const sf::Vector2f& velocity);
        void apply_friction(const sf::Vector2f& friction);
        void accelerate(const sf::Vector2f& acceleration);
        void move(Direction dir);
        void set_acceleration(const sf::Vector2f& acceleration);
        void set_velocity(const sf::Vector2f& velicity);
        sf::Vector2f get_velocity() const;
        sf::Vector2f get_speed() const;
        sf::Vector2f get_acceleration() const;
        float get_max_velocity() const;
        void set_direction(Direction dir);

    private:
        sf::Vector2f m_velocity;
        float m_velocityMax;
        sf::Vector2f m_speed;
        sf::Vector2f m_acceleration;
        Direction m_direction;
    };
} // namespace Engine
