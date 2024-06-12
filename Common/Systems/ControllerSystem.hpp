#pragma once

#include "System.hpp"

namespace Engine
{
    class ControllerSystem : public System, public std::enable_shared_from_this<ControllerSystem>
    {
    public:
        ControllerSystem(std::shared_ptr<SystemManager> system_manager);
        ~ControllerSystem();

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
    private:
        void move_entity(EntityId entity, Direction direction);
    };
    
    
    
} // namespace Engine
