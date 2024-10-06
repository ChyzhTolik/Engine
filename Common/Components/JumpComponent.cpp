#include "JumpComponent.hpp"

namespace Engine
{
    JumpComponent::JumpComponent(/* args */) : Component(ComponentType::Jump), m_grounded(false)
    {
    }
    
    JumpComponent::~JumpComponent()
    {
    }

    void to_json(json& j, const JumpInfo& p) 
    {
        j=json{
            {"mass", p.mass},
            {"jump_force", p.jump_force}
        };
    }

    void from_json(const json& j, JumpInfo& p) 
    {
        j.at("mass").get_to(p.mass);
        j.at("jump_force").get_to(p.jump_force);
    }

    std::unique_ptr<Component> JumpComponentCreator::create()
    {
        return std::make_unique<JumpComponent>();
    }

    void JumpComponent::read_in(json data)
    {
        m_jump_info = data;
    }

    void JumpComponent::jump()
    {
        m_jump_velocity = m_jump_info.jump_force;
        m_grounded = false;
    }

    float JumpComponent::get_jump_velocity() const
    {
        return m_jump_velocity;
    }

    bool JumpComponent::is_grounded() const
    {
        return m_grounded;
    }

    void JumpComponent::set_jump_velocity(float velocity)
    {
        m_jump_velocity = velocity;
    }

    float JumpComponent::get_mass() const
    {
        return m_jump_info.mass;
    }

    void JumpComponent::set_grounded(bool grounded)
    {
        m_grounded = grounded;
    }
} // namespace Engine
