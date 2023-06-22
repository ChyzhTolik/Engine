#include "testing.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"

namespace Test
{
    void test()
    {
        std::cout<<"Hello"<<std::endl;
    }

    int test_sfml()
    {
        sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

        return 0;
    }

    int test_animation()
    {
        //Creation of the window
        sf::RenderWindow window(sf::VideoMode({600,800}),"Example animation");
        //load of the texture image
        Engine::ResourceManager<sf::Texture,int> textures;
        Engine::TexturePtr texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("media/img/eye.png"))
        {
            return -1;
        }
        
        textures.load(0,"media/img/eye.png");
        //Creation of the different animations
        std::shared_ptr<Engine::Animation> walkLeft = std::make_shared<Engine::Animation>(texture);
        walkLeft->add_frames_line(4,2,0);
        std::shared_ptr<Engine::Animation> walkRight = std::make_shared<Engine::Animation>(texture);
        walkRight->add_frames_line(4,2,1);
        //Creation of the animates sprite
        Engine::AnimatedSprite sprite(walkLeft,Engine::AnimatedSprite::Status::Playing,sf::seconds(0.1));
        //game loop
        sf::Clock clock;
        while (window.isOpen())
        {
            sf::Time delta = clock.restart();
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) //close event
                window.close();
            }

            float speed = 50; // the movement speed of the entity

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //move left
            {
                sprite.set_animation(walkLeft);
                sprite.play();
                sprite.move({-speed*delta.asSeconds(),0});
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            //move right
            {
                sprite.set_animation(walkRight);
                sprite.play();
                sprite.move({speed*delta.asSeconds(),0});
            }

            window.clear();
            sprite.update(delta); //update the animate sprite for possible frame change
            window.draw(sprite); //display the animation
            window.display();
        }
        return 0;
    }

    int test_mushroom()
    {
        Engine::Game game;
        game.run();
    }
} // namespace Test