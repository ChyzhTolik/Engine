#pragma once

#include "BaseState.hpp"

namespace Engine
{
    class StateManager;

    class State_Game : public BaseState
    {
    private:
        /* data */
    public:
        State_Game(StateManager& l_stateManager);
        ~State_Game();
    };
    
    State_Game::State_Game(StateManager& l_stateManager) : BaseState(l_stateManager)
    {
    }
    
    State_Game::~State_Game()
    {
    }
    
} // namespace Engine
