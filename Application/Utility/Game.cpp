#include "Game.hpp"
#include <iostream>

namespace Engine
{
    Game::Game(sf::Texture& texture) : m_window("Engine", {800,600}), m_mushroom(texture), m_sprite(texture), m_texture(texture)
    {
        // m_mushroom_texture.loadFromFile("../media/img/Mushroom.png");
        // m_mushroom.setTexture(m_mushroom_texture);
        m_clock.restart();
        srand(time(nullptr));

        m_sprite.setOrigin({m_texture.getSize().x / 2, m_texture.getSize().y / 2});
        m_sprite.setPosition({0,0});

        m_window.GetEventManager()->AddCallback("Move",&Game::MoveSprite,this);
    }

    Game::~Game()
    {

    }

    void Game::update()
    {
        m_window.Update();
        move_mushroom();
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
        m_window.Draw(m_mushroom);
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
        while(!get_window().IsDone()){
            handle_input();
            update();
            render();
            RestartClock();
        }
    }

    void Game::handle_input()
    {

    }

    void Game::MoveSprite(EventDetails* l_details)
    {
        sf::Vector2i mousepos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
        m_sprite.setPosition({mousepos.x, mousepos.y});
        std::cout << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
    }
} // namespace Engine