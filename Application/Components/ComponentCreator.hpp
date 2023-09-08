#pragma once

#include "Component.hpp"
#include <memory>

namespace Engine
{
    // enum class ComponentType
    // {
    //     Position = 0, 
    //     SpriteSheet, 
    //     State, 
    //     Movable, 
    //     Controller, 
    //     Collidable
    // };

    class ComponentCreator
    {
    public:
        ComponentCreator(ComponentType type) : m_type(type){}
        virtual std::unique_ptr<Component> create() = 0;

    protected:
        ComponentType m_type;
    };

    class PositionCompCreator : public ComponentCreator
    {
    public:
        PositionCompCreator();
        std::unique_ptr<Component> create() override;
    };

    class MovementCompCreator : public ComponentCreator
    {
    public:
        MovementCompCreator();
        std::unique_ptr<Component> create() override;
    };

    class SpriteSheetCompCreator : public ComponentCreator
    {
    public:
        SpriteSheetCompCreator();
        std::unique_ptr<Component> create() override;
    };

    class StateCompCreator : public ComponentCreator
    {
    public:
        StateCompCreator();
        std::unique_ptr<Component> create() override;
    };

    class ControllerCompCreator : public ComponentCreator
    {
    public:
        ControllerCompCreator();
        std::unique_ptr<Component> create() override;
    };

    class CollisionCompCreator : public ComponentCreator
    {
    public:
        CollisionCompCreator();
        std::unique_ptr<Component> create() override;
    };

} // namespace Engine
