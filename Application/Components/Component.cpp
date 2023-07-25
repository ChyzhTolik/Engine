#include "Component.hpp"

namespace Engine
{
    Component::Component(ComponentType type) : m_type(type)
    {
    }
    
    Component::~Component()
    {
    }

    ComponentType Component::get_type() const
    {
        return m_type;
    }
} // namespace Engine
