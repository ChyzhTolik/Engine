#pragma once

#include "BaseState.hpp"
#include "ActionFunctinoid.hpp"

namespace Engine
{
    class GameCreator : public StateCreator
    {
    public:
        GameCreator(StateManager& l_state_manager, const sf::Texture& l_texture);
        GameCreator(StateManager& l_state_manager, const sf::Sprite& l_sprite);
        virtual std::unique_ptr<BaseState> create() override;
    private:
        const sf::Texture& m_texture;
        std::shared_ptr<sf::Sprite> m_sprite;
    };

    class State_Game : public BaseState
    {
    private:
        sf::Sprite m_game_sprite;
        sf::Vector2f m_increment;

        class PauseAction : public ActionFunctinoid
        {
        public:
            PauseAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

        class MainMenuAction : public ActionFunctinoid
        {
        public:
            MainMenuAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

    public:
        State_Game(StateManager& l_stateManager, const sf::Texture& l_textrue);
        State_Game(StateManager& l_stateManager, const sf::Sprite& l_sprite);
        ~State_Game();

        virtual void OnCreate() override;
        virtual void OnDestroy() override;

        virtual void Activate() override;
        virtual void Deactivate() override;

        virtual void Update(const sf::Time& l_time) override;
        virtual void Draw() override;
    };
    
} // namespace Engine
