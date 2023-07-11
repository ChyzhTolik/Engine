#include "Character.hpp"

namespace Engine
{
    Character::Character(EntityManager& l_entityMgr):
        EntityBase(l_entityMgr),
        m_spriteSheet(),
        m_jumpVelocity(250), 
        m_hitpoints(5)
    { 
        m_name = "Character"; 
    }

    Character::~Character()
    {
        
    }

    void Character::Move(const Direction& l_dir)
    {
        if (GetState() == EntityState::Dying)
        { 
            return; 
        }

        m_spriteSheet.SetDirection(l_dir);

        if (l_dir == Direction::Left)
        { 
            Accelerate(-m_speed.x, 0); 
        }

        else 
        { 
            Accelerate(m_speed.x, 0); 
        }

        if (GetState() == EntityState::Idle)
        {
            SetState(EntityState::Walking);
        }
    }

    void Character::Jump()
    {
        if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping || GetState() == EntityState::Hurt)
        {
            return;
        }

        SetState(EntityState::Jumping);
        AddVelocity(0, -m_jumpVelocity);
    }

    void Character::Attack()
    {
        if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping || GetState() == EntityState::Hurt || GetState() == EntityState::Attacking)
        {
            return;
        }

        SetState(EntityState::Attacking);
    }

    void Character::GetHurt(const int& l_damage)
    {
        if (GetState() == EntityState::Dying || GetState() == EntityState::Hurt)
        {
            return;
        }

        m_hitpoints = (m_hitpoints - l_damage > 0 ?
        m_hitpoints - l_damage : 0);

        if (m_hitpoints)
        { 
            SetState(EntityState::Hurt); 
        }
        else 
        { 
            SetState(EntityState::Dying); 
        }
    }

    void Character::Load(const std::string& l_path)
    {

    }

    void Character::UpdateAttackAABB()
    {
        m_attackAABB.left = (m_spriteSheet.GetDirection() == Direction::Left ?
            (m_AABB.left - m_attackAABB.width) - m_attackAABBoffset.x : (m_AABB.left + m_AABB.width) + m_attackAABBoffset.x);

        m_attackAABB.top = m_AABB.top + m_attackAABBoffset.y;
    }

    void Character::Animate()
    {
        EntityState state = GetState();

        if(state == EntityState::Walking && m_spriteSheet.get_current_type() != AnimationType::Running)
        {
            m_spriteSheet.SetAnimation(AnimationType::Running,true,true);
        }
        else if(state == EntityState::Jumping && m_spriteSheet.get_current_type() != AnimationType::Jumping)
        {
            m_spriteSheet.SetAnimation(AnimationType::Jumping,true,false);
        }
        else if(state == EntityState::Attacking && m_spriteSheet.get_current_type() != AnimationType::Firing)
        {
            m_spriteSheet.SetAnimation(AnimationType::Firing,true,false);
        } 
        else if(state == EntityState::Dying && m_spriteSheet.get_current_type() != AnimationType::Death)
        {
            m_spriteSheet.SetAnimation(AnimationType::Death,true,false);
        }
        else if(state == EntityState::Idle && m_spriteSheet.get_current_type() != AnimationType::Idle)
        {
            m_spriteSheet.SetAnimation(AnimationType::Idle,true,true);
        }
    }

    void Character::Update(float l_dT)
    {
        EntityBase::Update(l_dT);

        if(m_attackAABB.width != 0 && m_attackAABB.height != 0)
        {
            UpdateAttackAABB();
        }

        if(GetState() != EntityState::Dying && GetState() != EntityState::Attacking && GetState() != EntityState::Hurt)
        {
            if(abs(m_velocity.y) >= 0.001f)
            {
                SetState(EntityState::Jumping);
            } 
            else if(abs(m_velocity.x) >= 0.1f)
            {
                SetState(EntityState::Walking);
            } 
            else 
            {
                SetState(EntityState::Idle);
            }
        } 
        else if(GetState() == EntityState::Attacking || GetState() == EntityState::Hurt)
        {
            if(!m_spriteSheet.GetCurrentAnim()->is_playing())
            {
                SetState(EntityState::Idle);
            }
        } 
        else if(GetState() == EntityState::Dying)
        {
            if(!m_spriteSheet.GetCurrentAnim()->is_playing())
            {
                m_entityManager.Remove(m_id);
            }
        }

        Animate();
        m_spriteSheet.Update(l_dT);
        m_spriteSheet.SetSpritePosition(m_position);
    }

    void Character::Draw(sf::RenderWindow& l_wind)
    {
        m_spriteSheet.Draw(l_wind);
    }
} // namespace Engine
