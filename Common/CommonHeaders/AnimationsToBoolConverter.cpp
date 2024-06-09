#include "AnimationsToBoolConverter.hpp"

namespace Engine
{
    bool AnimationsToBoolConverter::is_attack(KnightAnimations animation)
    {
        return animation==KnightAnimations::Attack;
    }

    bool AnimationsToBoolConverter::is_death(KnightAnimations animation)
    {
        return animation==KnightAnimations::Death;
    }
} // namespace Engine
