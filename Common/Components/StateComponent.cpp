#include "StateComponent.hpp"

namespace Engine
{
    StateComponent::StateComponent(/* args */) : Component(ComponentType::State)
    {
    }
    
    StateComponent::~StateComponent()
    {
    }

    void to_json(json& j, const StateInfo& p) 
    {
        j=json{
            {"state", p.state}
        };
    }

    void from_json(const json& j, StateInfo& p) 
    {
        j.at("state").get_to(p.state);
    }

    void StateComponent::read_in(json data)
    {
        m_state_info = data;
    }

    EntityState StateComponent::get_state() const
    {
        return m_state_info.state;
    }

    void StateComponent::set_state(EntityState state)
    {
        m_state_info.state = state;
    }

    StateComponentCreator::StateComponentCreator()
    {

    }

    std::unique_ptr<Component> StateComponentCreator::create()
    {
        return std::make_unique<StateComponent>();
    }

    json StateComponentTestHelper::get_json(const StateInfo& input)
    {
        json result;
        result = input;
        return result;
    }
} // namespace Engine
