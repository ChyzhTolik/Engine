#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace Engine
{
    struct JumpInfo
    {
        float jump_speed;
        float max_jump_velocity;
    };
    

    class JumpComponent : public Component
    {
    public:
        JumpComponent(/* args */);
        ~JumpComponent();

        void read_in(json data) override;
        void jump();
        float get_jump_velocity() const;
        void apply_gravity(float gravity);
    private:
        JumpInfo m_jump_info;
        float m_jump_velocity;
        float m_jump_acceleration;
    };
    
    class JumpComponentCreator : public ComponentCreator
    {
    public:
        JumpComponentCreator() = default;
        virtual ~JumpComponentCreator() = default;
        virtual std::unique_ptr<Component> create() override;
    };
    
} // namespace Engine
