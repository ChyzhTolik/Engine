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
    public:
        Component(ComponentType type);
        virtual ~Component();
        ComponentType get_type() const;
        virtual void load(std::stringstream& l_stream) = 0;
    private:
        ComponentType m_type;
    };    
} // namespace Engine
