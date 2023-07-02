#include "Game.hpp"
#include "StateManager.hpp"
#include <iostream>

namespace Engine
{
    Game::Game(sf::Texture& texture) : m_window("Engine", {800,600}), m_mushroom(texture), m_sprite(texture), m_texture(texture),
        m_context(m_window, m_window.GetEventManager()), m_state_manager(m_context)
    {
        m_clock.restart();
        srand(time(nullptr));

        m_state_manager.SwitchTo(StateType::Intro);
    }

    Game::~Game()
    {

    }

    void Game::update()
    {
        m_window.Update();
        m_state_manager.Update(m_elapsed);
    }

    void Game::move_mushroom()
    {
        sf::Vector2u l_windSize = m_window.GetWindowSize();
        sf::Vector2u l_textSize = m_mushroom_texture.getSize();

        if((m_mushroom.getPosition().x > l_windSize.x - l_textSize.x&&m_increment.x> 0) || (m_mushroom.getPosition().x < 0 &&m_increment.x< 0))
        {
            m_increment.x = -m_increment.x;
        }

        if((m_mushroom.getPosition().y > l_windSize.y - l_textSize.y&&m_increment.y> 0) || (m_mushroom.getPosition().y < 0 &&m_increment.y< 0))
        {
            m_increment.y = -m_increment.y;
        }

        m_mushroom.setPosition(
            {m_mushroom.getPosition().x + m_increment.x*m_elapsed.asSeconds(),
            m_mushroom.getPosition().y + m_increment.y*m_elapsed.asSeconds()}
        );
    }

    void Game::render()
    {
        m_window.BeginDraw();
        m_state_manager.Draw();
        m_window.EndDraw();
    }

    sf::Time Game::GetElapsed()
    { 
        return m_elapsed; 
    }

    void Game::RestartClock()
    { 
        m_elapsed += m_clock.restart();

        float frametime = 1.0f / 60.0f;
        if(m_elapsed.asSeconds() >= frametime)
        {
            // Do something 60 times a second.
            
            m_elapsed -= sf::seconds(frametime); // Subtracting.
        }
    }    

    Window& Game::get_window()
    { 
        return m_window; 
    }

    void Game::run()
    {
        while(!get_window().IsDone())
        {
            update();
            render();
            LateUpdate();
        }
    }

    void Game::handle_input()
    {

    }

    void Game::MoveSprite(EventDetails& l_details)
    {
        sf::Vector2i mousepos = m_window.GetEventManager().GetMousePos(m_window.GetRenderWindow());
        m_sprite.setPosition({static_cast<float>(mousepos.x), static_cast<float>(mousepos.y)});
        std::cout << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
    }

    void Game::Move::execute(EventDetails& l_details)
    {
        sf::Vector2i mousepos = m_game.m_window.GetEventManager().GetMousePos(m_game.m_window.GetRenderWindow());
        m_game.m_sprite.setPosition({static_cast<float>(mousepos.x), static_cast<float>(mousepos.y)});
        std::cout << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
    }
    
    Game::Move::Move(Game& game) : m_game(game)
    {

    }

    void Game::LateUpdate()
    {
        m_state_manager.ProcessRequests();
        RestartClock();
    }
} // namespace Engine
