#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace Engine
{
    struct JumpInfo
    {
        float mass;
        float jump_force;
    };
    

    class JumpComponent : public Component
    {
    public:
        JumpComponent(/* args */);
        ~JumpComponent();

        void read_in(json data) override;
        void jump();
        float get_jump_velocity() const;
        void set_jump_velocity(float velocity);
        float get_mass() const;
        bool is_grounded() const;
        void set_grounded(bool grounded);
    private:
        JumpInfo m_jump_info;
        float m_jump_velocity = 0.f;
        bool m_grounded;
        const float m_gravity = 9.8f;
    };
    
    class JumpComponentCreator : public ComponentCreator
    {
    public:
        JumpComponentCreator() = default;
        virtual ~JumpComponentCreator() = default;
        virtual std::unique_ptr<Component> create() override;
    };
    
} // namespace Engine
