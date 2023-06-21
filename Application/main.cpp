#include <testing.hpp>

#include "MainWindow.hpp"
#include "Configuration.hpp"
#include "ResourceManager.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

int main()
{
    // Engine::Configuration::Initialize();

    // Engine::MainWindow window;
    // window.run(60);
    //Creation of the window
    sf::RenderWindow window(sf::VideoMode({600,800}),"Example animation");
    //load of the texture image
    Engine::ResourceManager<sf::Texture,int> textures;
    textures.load(0,"media/img/eye.png");
    //Creation of the different animations
    Engine::Animation walkLeft(Engine::TexturePtr(&textures.get(0)));
    walkLeft.add_frames_line(4,2,0);
    Engine::Animation walkRight(Engine::TexturePtr(&textures.get(0)));
    walkRight.add_frames_line(4,2,1);
    //Creation of the animates sprite
    Engine::AnimatedSprite sprite(Engine::AnimationPtr(&walkLeft),Engine::AnimatedSprite::Status::Playing,sf::seconds(0.1));
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
            sprite.set_animation(Engine::AnimationPtr(&walkLeft));
            sprite.play();
            sprite.move({-speed*delta.asSeconds(),0});
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        //move right
        {
            sprite.set_animation(Engine::AnimationPtr(&walkRight));
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