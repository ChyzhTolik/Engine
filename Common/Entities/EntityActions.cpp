#include "EntityActions.hpp"

namespace Engine
{
    Jumper::Jumper(std::function<void()>& action) : m_action(action)
    {

    }

    void Jumper::execute()
    {
        m_action();
    }
} // namespace Engine
