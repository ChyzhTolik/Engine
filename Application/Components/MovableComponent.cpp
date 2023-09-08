#include "MovableComponent.hpp"

namespace Engine
{
    MovableComponent::MovableComponent() : Component(ComponentType::Movable), m_velocity(sf::Vector2f(0.f,0.f))
    {
    }
    
    MovableComponent::~MovableComponent()
    {
    }

    void MovableComponent::load(std::stringstream& l_stream)
    {
        l_stream >> m_velocityMax >> m_speed.x >> m_speed.y;
        unsigned int dir = 0;
        l_stream >> dir;
        m_direction = (Direction)dir;
    }

    void MovableComponent::add_velocity(const sf::Vector2f& velocity)
    {
        m_velocity += velocity;

        if(std::abs(m_velocity.x) > m_velocityMax)
        {
            m_velocity.x = m_velocityMax * (m_velocity.x / std::abs(m_velocity.x));
        }

        if(std::abs(m_velocity.y) > m_velocityMax)
        {
            m_velocity.y = m_velocityMax * (m_velocity.y / std::abs(m_velocity.y));
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
       m_acceleration += acceleration;
    }

    void MovableComponent::move(Direction dir)
    {
        if(dir == Direction::Up)
        {
            m_acceleration.y -= m_speed.y;
        } 
        else if (dir == Direction::Down)
        {
            m_acceleration.y += m_speed.y;
        } 
        else if (dir == Direction::Left)
        {
            m_acceleration.x -= m_speed.x;
        } 
        else if (dir == Direction::Right)
        {
            m_acceleration.x += m_speed.x;
        }
    }

    sf::Vector2f MovableComponent::get_velocity() const
    {
        return m_velocity;
    }

    sf::Vector2f MovableComponent::get_speed() const
    {
        return m_speed;
    }

    sf::Vector2f MovableComponent::get_acceleration() const
    {
        return m_acceleration;
    }
    
    void MovableComponent::set_acceleration(const sf::Vector2f& acceleration)
    {
        m_acceleration = acceleration;
    }

    void MovableComponent::set_velocity(const sf::Vector2f& velicity)
    {
        m_velocity = velicity;
    }

    float MovableComponent::get_max_velocity() const
    {
        return m_velocityMax;
    }

    void MovableComponent::set_direction(Direction dir)
    {
        m_direction = dir;
    }
} // namespace Engine
