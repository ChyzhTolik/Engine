#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include "Direction.hpp"

namespace Engine
{
    struct MovableInfo
    {
        float velocity_max;
        sf::Vector2f speed;
        Direction direction;
    };

    class MovableComponent : public Component
    {
    public:
        MovableComponent(/* args */);
        ~MovableComponent();

        void read_in(json data) override;
        void add_velocity(const sf::Vector2f& velocity);
        void apply_friction(const sf::Vector2f& friction);
        void accelerate(const sf::Vector2f& acceleration);
        void move(Direction direction);

        float get_max_velocity() const;
        Direction get_direction() const;
        sf::Vector2f get_speed() const;
        sf::Vector2f get_velocity() const;
        sf::Vector2f get_acceleration() const;
    private:
        MovableInfo m_movable_info;
        sf::Vector2f m_velocity;
        sf::Vector2f m_acceleration;
    };

    class MovComponentTestHelper
    {
    public:
        static json get_json(const MovableInfo& input);
    };

    class MovableComponentCreator : public ComponentCreator
    {
    public:
        MovableComponentCreator();
        virtual ~MovableComponentCreator(){};
        virtual std::shared_ptr<Component> create() override;
    protected:
    };
} // namespace Engine
