#pragma once

#include "System.hpp"
#include "JumpComponent.hpp"

namespace Engine
{
    class LayeredMap;

    class JumpSystem : public System, public std::enable_shared_from_this<JumpSystem>
    {
    public:
        JumpSystem(std::shared_ptr<SystemManager> system_manager);
        ~JumpSystem();

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
        void apply_gravity(float time, std::shared_ptr<JumpComponent> jump_component);
        void set_map(std::shared_ptr<LayeredMap> map);

    private:
        std::shared_ptr<LayeredMap> m_map;
        const float m_gravity = 9.8f;
        float m_jump_velocity;
    };
} // namespace Engine
