#include "ControllerComponent.hpp"

namespace Engine
{
    ControllerComponent::ControllerComponent() : Component(ComponentType::Controller)
    {
    }
    
    ControllerComponent::~ControllerComponent()
    {
    }

    void ControllerComponent::load(std::stringstream& l_stream)
    {

    }
} // namespace Engine
