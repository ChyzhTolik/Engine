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
            {"jump_acceleration", p.jump_acceleration}
        };
    }

    void from_json(const json& j, JumpInfo& p) 
    {
        j.at("jump_acceleration").get_to(p.jump_acceleration);
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

    }
} // namespace Engine
