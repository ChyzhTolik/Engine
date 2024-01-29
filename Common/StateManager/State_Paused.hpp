#pragma once

#include "BaseState.hpp"
#include "ActionFunctinoid.hpp"

namespace Engine
{
    class PauseCreator : public StateCreator
    {
    public:
        PauseCreator(StateManager& l_state_manager, const sf::Font& l_font);
        virtual std::unique_ptr<BaseState> create() override;
    private:
        const sf::Font& m_font;
    };

    class State_Paused : public BaseState
    {
    private:
        sf::Text m_text;
        sf::RectangleShape m_rect;

        class UnpauseAction : public ActionFunctinoid
        {
        public:
            UnpauseAction(State_Paused& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Paused& m_state;
        };
    public:
        State_Paused(StateManager& l_stateManager, const sf::Font& l_font);
        ~State_Paused();

        virtual void OnCreate() override;
        virtual void OnDestroy() override;

        virtual void Activate() override;
        virtual void Deactivate() override;

        virtual void Update(const sf::Time& l_time) override;
        virtual void Draw() override;
    };
    
} // namespace Engine
