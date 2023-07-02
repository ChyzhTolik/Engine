#pragma once

#include "BaseState.hpp"
#include "ActionFunctinoid.hpp"

namespace Engine
{
    class MenuCreator : public StateCreator
    {
    public:
        MenuCreator(StateManager& l_state_manager, const sf::Font& l_font);
        virtual std::unique_ptr<BaseState> create() override;
    private:
        const sf::Font& m_font;
    };

    class State_MainMenu : public BaseState
    {
    private:
        sf::Text m_text;
        sf::Font m_font;
        sf::Vector2f m_buttonSize;
        sf::Vector2f m_buttonPos;
        unsigned int m_buttonPadding;
        sf::RectangleShape m_rects[3];
        std::vector<sf::Text> m_labels;
    public:
        State_MainMenu(StateManager& l_stateManager, const sf::Font& l_font);
        ~State_MainMenu();

        class MouseClickAction : public ActionFunctinoid
        {
        public:
            MouseClickAction(State_MainMenu& state);
            virtual void execute() override;
        private:
            State_MainMenu& m_state;
        };

        // Inherited via BaseState
        virtual void OnCreate() override;
        virtual void OnDestroy() override;
        virtual void Activate() override;
        virtual void Deactivate() override;
        virtual void Update(const sf::Time& l_time) override;
        virtual void Draw() override;
    };
    
} // namespace Engine
