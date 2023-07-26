#pragma once

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Engine
{
    enum class ComponentType
    {
        Position = 0, 
        SpriteSheet, 
        State, 
        Movable, 
        Controller, 
        Collidable
    };

    class Component
    {
    private:
        ComponentType m_type;
    public:
        Component(ComponentType type);
        virtual ~Component();
        ComponentType get_type() const;
        virtual void load(std::stringstream& l_stream) = 0;
    };    
} // namespace Engine
