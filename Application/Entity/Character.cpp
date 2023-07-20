#include "Character.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using nlohmann::json;

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
        m_direction = l_dir;

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

        if (m_hitpoints > 0)
        { 
            SetState(EntityState::Hurt); 
        }
        else 
        { 
            SetState(EntityState::Dying); 
        }
    }

    void to_json(json& j, const CharInfo& p);
    void from_json(const json& j, CharInfo& p);

    void Character::Load(const std::string& l_path)
    {
        std::ifstream char_file;
        char_file.open(l_path);

        if (!char_file.is_open())
        { 
            std::cout << "! Failed loading "<<l_path<<"." << std::endl; return; 
        }

	    json jf = json::parse(char_file);
        CharInfo char_info = jf;

        m_name = char_info.Name;
        m_hitpoints = char_info.Hitpoints;
        m_attackAABBoffset = char_info.DamageBox.getPosition();
        m_attackAABB.width = char_info.DamageBox.width;
        m_attackAABB.height = char_info.DamageBox.height;
        SetSize(char_info.BoundingBox.x, char_info.BoundingBox.y);
        std::string file_full_path = "media/Json/" + char_info.Animations;
        m_spriteSheet.LoadSheet(file_full_path, char_info.Spritesheet);
        m_speed = char_info.Speed;
        m_jumpVelocity = char_info.JumpVelocity;
        m_maxVelocity = char_info.MaxVelocity;

        char_file.close();
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
        else if(state == EntityState::Attacking && m_spriteSheet.get_current_type() != AnimationType::Attacking)
        {
            m_spriteSheet.SetAnimation(AnimationType::Attacking,true,false);
        } 
        else if(state == EntityState::Dying && m_spriteSheet.get_current_type() != AnimationType::Death)
        {
            m_spriteSheet.SetAnimation(AnimationType::Death,true,false);
        }
        else if(state == EntityState::Idle && m_spriteSheet.get_current_type() != AnimationType::Idle)
        {
            m_spriteSheet.SetAnimation(AnimationType::Idle,true,true);
        }
        else if(state == EntityState::Hurt && m_spriteSheet.get_current_type() != AnimationType::Hurt)
        {
            m_spriteSheet.SetAnimation(AnimationType::Hurt,true,false);
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

    void to_json(json& j, const CharInfo& p)
    {
        j = json
        { 
            {"Name", p.Name},
            {"Spritesheet", p.Spritesheet},
            {"Animations", p.Animations},
            {"Hitpoints", p.Hitpoints},
            {"BoundingBox", {p.BoundingBox.x, p.BoundingBox.y}},
            {"DamageBox", {p.DamageBox.left, p.DamageBox.top,p.DamageBox.width,p.DamageBox.height}},
            {"Speed", {p.Speed.x, p.Speed.y}},
            {"JumpVelocity", p.JumpVelocity},
            {"MaxVelocity", {p.MaxVelocity.y, p.MaxVelocity.y}}
        };
    }

    void from_json(const json& j, CharInfo& p) 
    {
        j.at("Name").get_to(p.Name);
        j.at("Spritesheet").get_to(p.Spritesheet);
        j.at("Animations").get_to(p.Animations);
        j.at("Hitpoints").get_to(p.Hitpoints);

        unsigned int vec_u[2];
        j.at("BoundingBox").get_to(vec_u);
        p.BoundingBox = {vec_u[0], vec_u[1]};

        float rect_f[4];
        j.at("DamageBox").get_to(rect_f);
        p.DamageBox = {{rect_f[0],rect_f[1]},{rect_f[2],rect_f[3]}};

        float vec_f[2];
        j.at("Speed").get_to(vec_f);
        p.Speed = {vec_f[0], vec_f[1]};

        j.at("JumpVelocity").get_to(p.JumpVelocity);
        
        j.at("MaxVelocity").get_to(vec_f);
        p.MaxVelocity={vec_f[0],vec_f[1]};
    }
} // namespace Engine
