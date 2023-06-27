#pragma once

#include "Window.hpp"
#include "ActionFunctinoid.hpp"

namespace Engine
{
    class Game
    {
    private:
        Window m_window;
        sf::Sprite m_mushroom;
        sf::Texture m_mushroom_texture;
        sf::Vector2i m_increment;
        sf::Clock m_clock;
	    sf::Time m_elapsed;
        sf::Sprite m_sprite;
        sf::Texture m_texture;

    public:
        Game(sf::Texture& texture);
        ~Game();
        Window& get_window();
        void run();
        sf::Time GetElapsed();
	    void RestartClock();
        void MoveSprite(EventDetails& l_details);

    private:
        class Move : public ActionFunctinoid
        {
        public:
            Move(Window& l_window, sf::Sprite& l_sprite);
            virtual void execute() override;
        private:
            Window& m_window;
            sf::Sprite& m_sprite;
        };

        std::unique_ptr<ActionFunctinoid> m_move_action;

        void handle_input();
        void update();
        void render();
        void move_mushroom();
    };    
} // namespace Engine

