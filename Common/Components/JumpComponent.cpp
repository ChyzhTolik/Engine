#include "JumpComponent.hpp"

namespace Engine
{
    JumpComponent::JumpComponent(/* args */) : Component(ComponentType::Jump)
    {
    }
    
    JumpComponent::~JumpComponent()
    {
    }

    void to_json(json& j, const JumpInfo& p) 
    {
        j=json{
            {"jump_speed", p.jump_speed},
            {"max_jump_velocity", p.max_jump_velocity}
        };
    }

    void from_json(const json& j, JumpInfo& p) 
    {
        j.at("jump_speed").get_to(p.jump_speed);
        j.at("max_jump_velocity").get_to(p.max_jump_velocity);
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
        m_jump_acceleration+=m_jump_info.jump_speed;
    }

    float JumpComponent::get_jump_velocity() const
    {
        return m_jump_velocity;
    }

    void JumpComponent::apply_gravity(float gravity)
    {
        m_jump_acceleration-=gravity;
    }
} // namespace Engine
