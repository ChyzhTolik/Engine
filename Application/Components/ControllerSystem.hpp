#pragma once

#include "System.hpp"
#include "Direction.hpp"

namespace Engine
{
    class ControllerSystem : public System
    {
    public:
        ControllerSystem(std::shared_ptr<SystemManager> l_system_manager);
        ~ControllerSystem();
        void Update(float l_dT) override;
        void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
        void Notify(const Message& l_message) override;
    private:
        void MoveEntity(const EntityId& l_entity, const Direction& l_dir);
    };
    
    
    
} // namespace Engine
