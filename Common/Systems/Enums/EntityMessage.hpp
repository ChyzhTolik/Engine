#pragma once

namespace Engine
{
    enum class EntityMessage
    {
        Move, 
        Is_Moving, 
        State_Changed, 
        Direction_Changed,
        Switch_State, 
        Attack_Action, 
        Dead,
        Jump,
        Is_Jumping,
        Fall
    };
} // namespace Engine
