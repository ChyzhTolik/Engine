#pragma once

#include "BaseState.hpp"

namespace Engine
{
    class State_Paused : public BaseState
    {
    private:
        /* data */
    public:
        State_Paused(StateManager& l_stateManager);
        ~State_Paused();
    };
    
    State_Paused::State_Paused(StateManager& l_stateManager) : BaseState(l_stateManager)
    {
    }
    
    State_Paused::~State_Paused()
    {
    }
    
} // namespace Engine
