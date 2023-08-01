#include "ControllerSystem.hpp"

namespace Engine
{
    ControllerSystem::ControllerSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::Control, l_system_manager)
    {
    }
    
    ControllerSystem::~ControllerSystem()
    {
    }
} // namespace Engine
