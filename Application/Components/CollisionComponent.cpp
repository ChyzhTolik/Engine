#include "CollisionComponent.hpp"

namespace Engine
{
    CollisionComponent::CollisionComponent(/* args */) : Component(ComponentType::Collidable), 
        m_origin(Origin::Mid_Bottom), 
        m_collidingOnX(false),
        m_collidingOnY(false)
    {
    }
    
    CollisionComponent::~CollisionComponent()
    {
    }

    void CollisionComponent::load(std::stringstream& l_stream)
    {
        unsigned int origin = 0;
        l_stream >> m_AABB.width >> m_AABB.height >> m_offset.x >> m_offset.y >> origin;
        m_origin = (Origin)origin;
    }

    void CollisionComponent::CollideOnX()
    { 
        m_collidingOnX = true; 
    }

    void CollisionComponent::CollideOnY()
    { 
        m_collidingOnY = true; 
    }

    void CollisionComponent::ResetCollisionFlags()
    {
        m_collidingOnX = false;
        m_collidingOnY = false;
    }

    void CollisionComponent::SetSize(const sf::Vector2f& l_vec)
    {
        m_AABB.width = l_vec.x;
        m_AABB.height = l_vec.y;
    }

    void CollisionComponent::SetPosition(const sf::Vector2f& l_vec)
    {
        switch(m_origin)
        {
            case(Origin::Top_Left):
                m_AABB.left = l_vec.x + m_offset.x;
                m_AABB.top = l_vec.y + m_offset.y;
            break;

            case(Origin::Abs_Centre):
                m_AABB.left = l_vec.x - (m_AABB.width / 2) + m_offset.x;
                m_AABB.top = l_vec.y - (m_AABB.height / 2) + m_offset.y;
            break;

            case(Origin::Mid_Bottom):
                m_AABB.left = l_vec.x - (m_AABB.width / 2) + m_offset.x;
                m_AABB.top = l_vec.y - m_AABB.height + m_offset.y;
            break;
        }
    }

    const sf::FloatRect& CollisionComponent::GetCollidable() const
    { 
        return m_AABB; 
    }
} // namespace Engine
