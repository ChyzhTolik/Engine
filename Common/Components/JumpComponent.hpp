#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace Engine
{
    struct JumpInfo
    {
        float jump_acceleration;
    };
    

    class JumpComponent : public Component
    {
    public:
        JumpComponent(/* args */);
        ~JumpComponent();

        void read_in(json data) override;
        void jump();
    private:
        JumpInfo m_jump_info;
    };
    
    class JumpComponentCreator : public ComponentCreator
    {
    public:
        JumpComponentCreator() = default;
        virtual ~JumpComponentCreator() = default;
        virtual std::unique_ptr<Component> create() override;
    };
    
} // namespace Engine
