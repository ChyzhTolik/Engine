#pragma once

#include "BaseState.hpp"
#include "ActionFunctinoid.hpp"

namespace Engine
{
    class State_Intro : public BaseState
    {
    private:
        sf::Sprite m_introSprite;
        sf::Text m_text;
        sf::Font m_font;
        float m_timePassed;

        class ContinueAction : public ActionFunctinoid
        {
        public:
            ContinueAction(State_Intro& state);
            virtual void execute() override;
        private:
            State_Intro& m_state;
        };
    public:
        State_Intro(StateManager& l_stateManager, const sf::Texture& l_texture, const sf::Font& font);
        ~State_Intro();
        virtual void OnCreate() override;
        virtual void OnDestroy() override;

        virtual void Activate() override;
        virtual void Deactivate() override;

        virtual void Update(const sf::Time& l_time) override;
        virtual void Draw() override;
    };    
} // namespace Engine
