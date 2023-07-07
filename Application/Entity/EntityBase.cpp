#include "EntityBase.hpp"

namespace Engine
{
    EntityBase::EntityBase(std::shared_ptr<EntityManager> l_entityMgr)
        :m_entityManager(l_entityMgr), m_name("BaseEntity"),
        m_type(EntityType::Base), m_referenceTile(nullptr),
        m_state(EntityState::Idle), m_id(0),
        m_collidingOnX(false), m_collidingOnY(false)
    {

    }

    void EntityBase::SetPosition(const float& l_x, const float& l_y)
    {
        m_position = sf::Vector2f(l_x,l_y);
        UpdateAABB();
    }
    
    void EntityBase::SetPosition(const sf::Vector2f& l_pos)
    {
        m_position = l_pos;
        UpdateAABB();
    }

    void EntityBase::SetSize(const float& l_x, const float& l_y)
    {
        m_size = sf::Vector2f(l_x,l_y);
        UpdateAABB();
    }

    void EntityBase::SetState(const EntityState& l_state)
    {
        if(m_state == EntityState::Dying){ return; }
        m_state = l_state;
    }
} // namespace Engine
