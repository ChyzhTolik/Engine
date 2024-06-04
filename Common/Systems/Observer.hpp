#pragma once

#include "Message.hpp"

namespace Engine
{
    class Observer{
    public:
        virtual ~Observer(){}
        virtual void notify(const Message& l_message) = 0;
    };
} // namespace Engine
