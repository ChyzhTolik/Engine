#pragma once

#include <functional>

namespace Engine
{
    class EntityAction // functinoid
    {
    public:
        virtual ~EntityAction() = default;
        virtual void execute() = 0;
    };

    class Jumper : public EntityAction
    {
    public:
        Jumper(std::function<void()>& action);
        void execute() override;
    private:
        std::function<void()>& m_action;
    };

} // namespace Engine
