#include "StateComponent.hpp"

namespace Engine
{
    StateComponent::StateComponent(/* args */) : Component(ComponentType::State)
    {
    }
    
    StateComponent::~StateComponent()
    {
    }

    void StateComponent::load(std::stringstream& l_stream)
    {
        unsigned int state = 0;
        l_stream >> state;
        m_state = EntityState(state);
    }

    EntityState StateComponent::GetState() const
    { 
        return m_state; 
    }

    void StateComponent::SetState(const EntityState& l_state)
    {
        m_state = l_state;
    }
} // namespace Engine
