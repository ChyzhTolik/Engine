#pragma once

#include "Component.hpp"
#include "EntityState.hpp"

namespace Engine
{
    struct StateInfo
    {
        EntityState state;
    };

    class StateComponent : public Component
    {
    public:
        StateComponent(/* args */);
        ~StateComponent();

        void read_in(json data) override;
        EntityState get_state() const;
        void set_state(EntityState state);
    private:
        StateInfo m_state_info;
    };

    class StateComponentCreator : public ComponentCreator
    {
    public:
        StateComponentCreator();
        virtual ~StateComponentCreator(){};
        virtual std::shared_ptr<Component> create() override;
    };

    class StateComponentTestHelper
    {
    public:
        static json get_json(const StateInfo& input);
    };
} // namespace Engine
