#pragma once

#include "Component.hpp"

namespace Engine
{
    class ControllerComponent : public Component
    {
    public:
        ControllerComponent();
        ~ControllerComponent();
        void load(std::stringstream& l_stream) override;
    private:
        /* data */
    };
    
} // namespace Engine
