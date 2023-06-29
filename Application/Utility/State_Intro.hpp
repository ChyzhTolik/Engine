#pragma once

#include "BaseState.hpp"

namespace Engine
{
    class State_Intro : public BaseState
    {
    private:
        private:
        sf::Texture m_introTexture;
        sf::Sprite m_introSprite;
        sf::Text m_text;
        float m_timePassed;
    public:
        State_Intro(StateManager& l_stateManager);
        ~State_Intro();
        void Continue(EventDetails& l_details);
        virtual void OnCreate(const sf::Texture& l_texture) override;
        virtual void OnDestroy() override;

        virtual void Activate() override;
        virtual void Deactivate() override;

        virtual void Update(const sf::Time& l_time) override;
        virtual void Draw() override;
    };    
} // namespace Engine
