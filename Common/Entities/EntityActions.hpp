#pragma once

#include <functional>

namespace Engine
{
    class EntityAction // functinoid
    {
        virtual ~EntityAction() = default;
        virtual void execute() = 0;
    };
} // namespace Engine
