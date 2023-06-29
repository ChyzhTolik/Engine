#pragma once

namespace Engine
{
    class ActionFunctinoid
    {
    public:
        virtual ~ActionFunctinoid(){}
        virtual void execute() = 0;
    };
    
} // namespace Engine

