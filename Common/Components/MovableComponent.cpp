#include "MovableComponent.hpp"

namespace Engine
{
    MovableComponent::MovableComponent(/* args */) : 
        Component(ComponentType::Movable),
        m_velocity{0,0},
        m_acceleration{0,0}
    {
    }
    
    MovableComponent::~MovableComponent()
    {
    }

        // float velocity_max;
        // sf::Vector2f speed;
        // Direction direction;

    void to_json(json& j, const MovableInfo& p) 
    {
        j=json{
            {"speed", {p.speed.x,p.speed.y}},
            {"velocity_max", p.velocity_max},
            {"direction", p.direction},
        };
    }

    void from_json(const json& j, MovableInfo& p) 
    {
        float float_array[2];
        j.at("speed").get_to(float_array);
        p.speed = sf::Vector2f(float_array[0],float_array[1]);

        j.at("velocity_max").get_to(p.velocity_max);
        j.at("direction").get_to(p.direction);
    }

    void MovableComponent::read_in(json data)
    {
        m_movable_info = data;
    }

    void MovableComponent::add_velocity(const sf::Vector2f& velocity)
    {
        m_velocity+=velocity;

        if(std::abs(m_velocity.x) > m_movable_info.velocity_max)
        {
            m_velocity.x = m_movable_info.velocity_max * (m_velocity.x / std::abs(m_velocity.x));
        }
        
        if(std::abs(m_velocity.y) > m_movable_info.velocity_max)
        {
            m_velocity.y = m_movable_info.velocity_max * (m_velocity.y / std::abs(m_velocity.y));
        }
    }

    void MovableComponent::apply_friction(const sf::Vector2f& friction)
    {
        if(m_velocity.x != 0 && friction.x != 0)
        {
            if(std::abs(m_velocity.x) - std::abs(friction.x) < 0)
            {
                m_velocity.x = 0;
            } 
            else 
            {
                m_velocity.x += (m_velocity.x > 0 ? friction.x * -1 : friction.x);
            }
        }

        if(m_velocity.y != 0 && friction.y != 0)
        {
            if(std::abs(m_velocity.y) - std::abs(friction.y) < 0)
            {
                m_velocity.y = 0;
            } 
            else 
            {
                m_velocity.y += (m_velocity.y > 0 ? friction.y * -1 : friction.y);
            }
        }
    }

    void MovableComponent::accelerate(const sf::Vector2f& acceleration)
    {
        m_acceleration+=acceleration;
    }

    void MovableComponent::move(Direction direction)
    {
        if(direction == Direction::Up)
        {
            m_acceleration.y -= m_movable_info.speed.y;
        } 
        else if (direction == Direction::Down)
        {
            m_acceleration.y += m_movable_info.speed.y;
        } 
        else if (direction == Direction::Left)
        {
            m_acceleration.x -= m_movable_info.speed.x;
        } 
        else if (direction == Direction::Right)
        {
            m_acceleration.x += m_movable_info.speed.x;
        }

        m_movable_info.direction = direction;
    }

    json MovComponentTestHelper::get_json(const MovableInfo& input)
    {
        json result;
        result = input;
        return result;
    }

    MovableComponentCreator::MovableComponentCreator()
    {

    }

    std::shared_ptr<Component> MovableComponentCreator::create()
    {
        return std::make_shared<MovableComponent>();
    }

    float MovableComponent::get_max_velocity() const
    {
        return m_movable_info.velocity_max;
    }

    Direction MovableComponent::get_direction() const
    {
        return m_movable_info.direction;
    }

    sf::Vector2f MovableComponent::get_speed() const
    {
        return m_movable_info.speed;
    }

    sf::Vector2f MovableComponent::get_velocity() const
    {
        return m_velocity;
    }

    sf::Vector2f MovableComponent::get_acceleration() const
    {
        return m_acceleration;
    }

    void MovableComponent::set_acceleration(const sf::Vector2f& acceleration)
    {
        m_acceleration = acceleration;
    }

    void MovableComponent::set_velocity(const sf::Vector2f& velocity)
    {
        m_velocity = velocity;
    }

    void MovableComponent::set_direction(Direction direction)
    {
        m_movable_info.direction = direction;
    }
} // namespace Engine
