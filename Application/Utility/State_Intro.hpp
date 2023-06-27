#pragma once

#include "BaseState.hpp"

namespace Engine
{
    class State_Intro : public BaseState
    {
    private:
        /* data */
    public:
        State_Intro(StateManager& l_stateManager);
        ~State_Intro();
    };
    
    State_Intro::State_Intro(StateManager& l_stateManager) : BaseState(l_stateManager)
    {
    }
    
    State_Intro::~State_Intro()
    {
    }
    
} // namespace Engine
