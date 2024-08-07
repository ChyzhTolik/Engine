#pragma once

#include "System.hpp"
#include "PositionComponent.hpp"

namespace Engine
{
    class JumpSystem : public System, public std::enable_shared_from_this<JumpSystem>
    {
    public:
        JumpSystem(std::shared_ptr<SystemManager> system_manager);
        ~JumpSystem();

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
        void jump();
    private:
    };
} // namespace Engine
