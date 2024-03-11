#pragma once

namespace Engine
{
    enum class AnimationType
    {
        None = -1,
        Idle,
        Running,
        Throwing,
        Firing,
        Siting,
        SitFiring,
        Jumping,
        JumpFiring,
        Death,
        Climbing,
        Attacking,
        Hurt,
    };
} // namespace Engine
