#pragma once

#include "System.hpp"

namespace Engine
{
    class ControllerSystem : public System
    {
    public:
        ControllerSystem(std::shared_ptr<SystemManager> l_system_manager);
        ~ControllerSystem();
        virtual void Update(float l_dT) = 0;
        virtual void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) = 0;
    private:
        /* data */
    };
    
    
    
} // namespace Engine
