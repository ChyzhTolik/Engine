#pragma once

#include "BaseState.hpp"
#include "ActionFunctinoid.hpp"

namespace Engine
{
    class GameCreator : public StateCreator
    {
    public:
        GameCreator(StateManager& l_state_manager, const sf::Texture& l_texture);
        virtual std::unique_ptr<BaseState> create() override;
    private:
        const sf::Texture& m_texture;
        std::shared_ptr<sf::Sprite> m_sprite;
    };

    class State_Game : public BaseState
    {
    private:
        sf::Sprite m_background_sprite;
        void UpdateCamera();

        class PauseAction : public ActionFunctinoid
        {
        public:
            PauseAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

        class ClickAction : public ActionFunctinoid
        {
        public:
            ClickAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

        class MoveAction : public ActionFunctinoid
        {
        public:
            MoveAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

        class AttackAction : public ActionFunctinoid
        {
        public:
            AttackAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

        class DieAction : public ActionFunctinoid
        {
        public:
            DieAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

        class JumpAction : public ActionFunctinoid
        {
        public:
            JumpAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

        class TypeAction : public ActionFunctinoid
        {
        public:
            TypeAction(State_Game& state);
            virtual void execute(EventDetails& l_details) override;
        private:
            State_Game& m_state;
        };

    public:
        State_Game(StateManager& l_stateManager, const sf::Texture& l_textrue);
        ~State_Game();

        virtual void OnCreate() override;
        virtual void OnDestroy() override;

        virtual void Activate() override;
        virtual void Deactivate() override;

        virtual void Update(const sf::Time& l_time) override;
        virtual void Draw() override;
    };
    
} // namespace Engine
