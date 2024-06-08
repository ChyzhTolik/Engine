#pragma once

#include "System.hpp"

namespace Engine
{
    class StateSystem : public System,  public std::enable_shared_from_this<StateSystem>
    {
    public:
        StateSystem(std::shared_ptr<SystemManager> system_manager);
        ~StateSystem();

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
    private:
        void change_state(EntityId id, EntityState state, bool force);
    };
    
} // namespace Engine
