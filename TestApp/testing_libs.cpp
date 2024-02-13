#include "testing_libs.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Configuration/Configuration.hpp"
#include "Window/Window.hpp"
#include "Game.hpp"
#include "Map/TileTemplate.hpp"
#include "Map/TileSetTemplate.hpp"
#include "Map/KnightTiles.hpp"
#include "Map/IsoTiles.hpp"
#include "Map/MapLayerTemplate.hpp"
#include "Map/LayeredMap.hpp"

#include <nlohmann/json.hpp>
using nlohmann::json;


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

	void test_tiles()
	{
		Engine::Configuration::Initialize();

		Engine::TileInfo<Engine::KnightTiles> temp_tile_info{Engine::KnightTiles::Brick, false,{0.2f,0.f},{32,0},{32,32}};
		Engine::TileTemplate<Engine::KnightTiles> temp_tile(temp_tile_info, Engine::Configuration::Textures::TilesEngine);

		auto t_info = temp_tile.get_tile_info();

		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);

		std::shared_ptr<Engine::TileSetTemplate<Engine::KnightTiles>> tile_set = std::make_shared<Engine::TileSetTemplate<Engine::KnightTiles>>();
		tile_set->load_from_file("media/Json/IsometricTiles.json");

		Engine::SharedContext context;

		context.m_wind = window;
		context.m_eventManager = context.m_wind->GetEventManager();

		std::shared_ptr<Engine::MapLayerInterface> map_layer = std::make_shared<Engine::MapLayerTemplate<Engine::KnightTiles>>(context);
		std::dynamic_pointer_cast<Engine::MapLayerTemplate<Engine::KnightTiles>>(map_layer)->set_tile_set(tile_set);
		map_layer->load_from_file("media/map/map_layer1.json");

		while (!window->IsDone())
		{
			window->Update();
			window->BeginDraw();
			map_layer->draw();
			
			window->EndDraw();
		}
	}

	void test_map()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);
		Engine::SharedContext context;

		context.m_wind = window;
		context.m_eventManager = context.m_wind->GetEventManager();

		Engine::LayeredMap layered_map(context);
		// layered_map.test_json();
		layered_map.load_from_file("media/map/map_info.json");
	}
} // namespace Test
