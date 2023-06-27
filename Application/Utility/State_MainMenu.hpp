#pragma once

#include "BaseState.hpp"

namespace Engine
{
    class State_MainMenu : public BaseState
    {
    private:
        /* data */
    public:
        State_MainMenu(StateManager& l_stateManager);
        ~State_MainMenu();
    };
    
    State_MainMenu::State_MainMenu(StateManager& l_stateManager) : BaseState(l_stateManager)
    {
    }
    
    State_MainMenu::~State_MainMenu()
    {
    }
    
} // namespace Engine
