#pragma once

#include "EventDetails.hpp"

namespace Engine
{
    class ActionFunctinoid
    {
    public:
        virtual ~ActionFunctinoid(){}

        virtual void execute(EventDetails& l_details) = 0;
    };
    
} // namespace Engine

