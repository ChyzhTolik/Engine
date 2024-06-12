#pragma once

#include "AnimationTypes.hpp"

namespace Engine
{
    class AnimationsToBoolConverter
    {
    public:
        static bool is_attack(KnightAnimations animation);
        static bool is_death(KnightAnimations animation);
    };
} // namespace Engine
