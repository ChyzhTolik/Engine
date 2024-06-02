#include "ControllerComponent.hpp"

namespace Engine
{
    ControllerComponent::ControllerComponent(/* args */): Component(ComponentType::Controller)
    {
    }
    
    ControllerComponent::~ControllerComponent()
    {
    }

    void ControllerComponent::read_in(json data)
    {

    }

    ControllerComponentCreator::ControllerComponentCreator()
    {

    }

    std::shared_ptr<Component> ControllerComponentCreator::create()
    {
        return std::make_shared<ControllerComponent>();
    }
} // namespace Engine
