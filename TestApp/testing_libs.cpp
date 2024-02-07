#include "testing_libs.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Configuration/Configuration.hpp"
#include "Window/Window.hpp"
#include "Game.hpp"

namespace Test
{
    void conf_init()
    {
        Engine::Configuration::Initialize();
    }

    int test_sfml()
	{
		Engine::Configuration::Initialize();
		sf::Sprite sprite(Engine::Configuration::textures.get(Engine::Configuration::Textures::Intro));
		sf::RenderWindow window(sf::VideoMode(sprite.getTexture()->getSize()), "SFML works!");

		std::cout<<"Width: "<<window.getSize().x<<std::endl;
		std::cout<<"Height: "<<window.getSize().y<<std::endl;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(sprite);
			window.display();
		}

		return 0;
	}

	void test_window()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);
		sf::Sprite sprite(Engine::Configuration::textures.get(Engine::Configuration::Textures::Intro));
		
		sf::Clock m_clock;
		sf::Time TimePerFrame = sf::seconds(1.f/60);

		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (!window->IsDone())
		{
			window->Update();
			window->BeginDraw();
			window->Draw(sprite);
			window->EndDraw();
		}
	}

	void test_states()
	{
		Engine::Configuration::Initialize();
		Engine::Game game;
		game.run(60);
	}
} // namespace Test
