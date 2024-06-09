#pragma once

#include "EntityState.hpp"
#include "AnimationTypes.hpp"

namespace Engine
{
    class AnimationsToStateConverter
    {
    public:
        static KnightAnimations convert(EntityState state);
    private:
        /* data */
    };
} // namespace Engine
