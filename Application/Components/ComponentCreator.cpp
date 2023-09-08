#include "ComponentCreator.hpp"

#include "PositionComp.hpp"
#include "MovableComponent.hpp"
#include "SpriteSheetComponent.hpp"
#include "StateComponent.hpp"
#include "ControllerComponent.hpp"
#include "CollisionComponent.hpp"

namespace Engine
{
    PositionCompCreator::PositionCompCreator() : ComponentCreator(ComponentType::Position)
    {
        
    }

    std::unique_ptr<Component> PositionCompCreator::create()
    {
        return std::make_unique<PositionComp>();
    }

    MovementCompCreator::MovementCompCreator() : ComponentCreator(ComponentType::Movable)
    {
        
    }

    std::unique_ptr<Component> MovementCompCreator::create()
    {
        return std::make_unique<MovableComponent>();
    }
    
    SpriteSheetCompCreator::SpriteSheetCompCreator() : ComponentCreator(ComponentType::SpriteSheet)
    {
        
    }

    std::unique_ptr<Component> SpriteSheetCompCreator::create()
    {
        return std::make_unique<SpriteSheetComponent>();
    }

    StateCompCreator::StateCompCreator() : ComponentCreator(ComponentType::State)
    {
        
    }

    std::unique_ptr<Component> StateCompCreator::create()
    {
        return std::make_unique<StateComponent>();
    }

    ControllerCompCreator::ControllerCompCreator() : ComponentCreator(ComponentType::Controller)
    {
        
    }

    std::unique_ptr<Component> ControllerCompCreator::create()
    {
        return std::make_unique<ControllerComponent>();
    }

    CollisionCompCreator::CollisionCompCreator() : ComponentCreator(ComponentType::Collidable)
    {
        
    }

    std::unique_ptr<Component> CollisionCompCreator::create()
    {
        return std::make_unique<CollisionComponent>();
    }
} // namespace Engine
