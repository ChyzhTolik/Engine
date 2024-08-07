#pragma once

#include <bitset>

namespace Engine
{
    enum class ComponentType
    {
        Position,
        SpriteSheet,
        State,
        Movable,
        Controller,
        Collidable,
        Jump,
        All
    };

    using ComponentBitSet = std::bitset<static_cast<size_t>(ComponentType::All)>;
} // namespace Engine
