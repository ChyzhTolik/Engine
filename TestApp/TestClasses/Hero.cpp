#include "Hero.hpp"

namespace Test
{
    Hero::Hero(const sf::Texture& texture): m_texture(texture), m_sprite(texture)
    {
    }
    
    Hero::~Hero()
    {
    }

    void Hero::init(const sf::Vector2f& position, const float mass)
    {
        m_position = position;
        m_mass = mass;

        m_grounded = false;
        m_sprite.setPosition(m_position);
        m_sprite.setOrigin({m_texture.getSize().x/2.f, m_texture.getSize().y/2.f});
    }

    void Hero::update(float dt)
    {
        m_velocity -= m_mass*m_gravity*dt;
        m_position.y -=m_velocity*dt;
        m_sprite.setPosition(m_position);

        if (m_position.y>=600*0.65f)
        {
            m_position.y = 600*0.65f;
            m_velocity=0;
            m_grounded = true;
            m_jump_count = 0;
        }
        else
        {
            m_position.x +=abs(300.f*dt);
        }
    }
    
    void Hero::jump(float velocity)
    {
        if(m_jump_count < 2)
        {
            m_jump_count++;
        }

        m_velocity = velocity;
        m_grounded = false;
    }
    
    sf::Sprite& Hero::get_sprite()
    {
        return m_sprite;
    }
} // namespace Test
