#pragma once

#include "Component.hpp"

namespace Engine
{
    class ControllerComponent : public Component
    {
    public:
        ControllerComponent(/* args */);
        ~ControllerComponent();

        void read_in(json data) override;
    private:
        /* data */
    };

    class ControllerComponentCreator : public ComponentCreator
    {
    public:
        ControllerComponentCreator();
        virtual ~ControllerComponentCreator(){};
        virtual std::shared_ptr<Component> create() override;
    };
} // namespace Engine
