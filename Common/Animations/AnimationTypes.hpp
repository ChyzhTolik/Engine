#pragma once

#include <string_view>

namespace Engine
{
    enum class KnightAnimations
    {
        None = -1,
        Idle,
        Walk,
        Jump,
        Attack,
        Hurt,
        Death,
    };
} // namespace Engine
