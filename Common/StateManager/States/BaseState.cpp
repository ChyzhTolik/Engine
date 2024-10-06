#include "BaseState.hpp"

namespace Engine
{
    StateCreator::StateCreator(StateManager& l_state_manager) : m_state_manager(l_state_manager)
    {
        
    };

    void BaseState::set_callback(std::function<void()> callback)
    {
        throw std::runtime_error("impossible");
    }
} // namespace Engine
