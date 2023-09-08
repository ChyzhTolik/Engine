#pragma once

#include "Component.hpp"

namespace Engine
{
    enum class EntityState{ Idle, Walking, Attacking, Hurt, Dying };

    class StateComponent : public Component
    {
    public:
        StateComponent(/* args */);
        ~StateComponent();
        void load(std::stringstream& l_stream) override;
        EntityState GetState() const;
        void SetState(const EntityState& l_state);
    private:
        EntityState m_state;
    };
    
    
    
} // namespace Engine
