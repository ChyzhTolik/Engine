#pragma once

#include "BaseState.hpp"
#include "ActionFunctinoid.hpp"

namespace Engine
{
    class IntroCreator : public StateCreator
    {
    public:
        IntroCreator(StateManager& l_state_manager, const sf::Texture& l_texture, const sf::Font& l_font);
        virtual std::unique_ptr<BaseState> create() override;
    private:
        const sf::Texture& m_texture;
        const sf::Font& m_font;
    };

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
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Intro& m_state;
        };
    public:
        State_Intro(StateManager& l_stateManager, const sf::Texture& l_texture, const sf::Font& font);
        virtual ~State_Intro(){};
        virtual void OnCreate() override;
        virtual void OnDestroy() override;

        virtual void Activate() override;
        virtual void Deactivate() override;

        virtual void Update(const sf::Time& l_time) override;
        virtual void Draw() override;
    };
} // namespace Engine
