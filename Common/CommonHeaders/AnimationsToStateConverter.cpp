#include "AnimationsToStateConverter.hpp"

namespace Engine
{
    KnightAnimations AnimationsToStateConverter::convert(EntityState state)
    {
        switch (state)
        {
        case EntityState::Idle:
            return KnightAnimations::Idle;
            break;

        case EntityState::Attacking:
            return KnightAnimations::Attack;
            break;
                
        case EntityState::Dying:
            return KnightAnimations::Death;
            break;

        case EntityState::Walking:
            return KnightAnimations::Walk;
            break;

        case EntityState::Hurt:
            return KnightAnimations::Hurt;
            break;

        case EntityState::Jumping:
            return KnightAnimations::Jump;
            break;
        
        default:
            break;
        }

        return KnightAnimations::None;
    }
} // namespace Engine
