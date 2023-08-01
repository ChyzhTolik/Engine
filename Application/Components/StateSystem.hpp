#pragma once

#include "System.hpp"
#include "StateComponent.hpp"

namespace Engine
{
    class StateSystem : public System, public std::enable_shared_from_this<StateSystem>
    {
    public:
        StateSystem(std::shared_ptr<SystemManager> l_system_manager);
        ~StateSystem();
        void Update(float l_dT) override;
        void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
        void ChangeState(const EntityId& l_entity, const EntityState& l_state, const bool& l_force);
        void Notify(const Message& l_message) override;
    private:
    };
} // namespace Engine
