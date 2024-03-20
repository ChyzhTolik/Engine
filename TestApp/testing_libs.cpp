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

#include "Animations/AnimatedSprite.hpp"
#include "Animations/SpriteSheetTemplate.hpp"
#include "Animations/AnimationTypes.hpp"
#include "Animations/Anim_Directional.hpp"

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
		// Engine::Configuration::Initialize();

		// Engine::TileInfo<Engine::KnightTiles> temp_tile_info{Engine::KnightTiles::Brick, false,{0.2f,0.f},{32,0},{32,32}};
		// Engine::TileTemplate<Engine::KnightTiles> temp_tile(temp_tile_info, Engine::Configuration::Textures::TilesEngine);

		// auto t_info = temp_tile.get_tile_info();

		// sf::Vector2u window_size{800,600};
		// std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);

		// std::shared_ptr<Engine::TileSetTemplate<Engine::KnightTiles>> tile_set = std::make_shared<Engine::TileSetTemplate<Engine::KnightTiles>>();
		// tile_set->load_from_file("media/Json/IsometricTiles.json");

		// Engine::TileSetFactory tile_set_factory;
		// auto tile_set_from_factory = tile_set_factory.get<Engine::IsoTiles>();
		// tile_set_from_factory->load_from_file("media/map/IsometricTiles.json");

		// Engine::SharedContext context;

		// context.m_wind = window;
		// context.m_eventManager = context.m_wind->GetEventManager();

		// std::shared_ptr<Engine::MapLayerInterface> map_layer = std::make_shared<Engine::MapLayerTemplate<Engine::IsoTiles>>(context);
		// std::dynamic_pointer_cast<Engine::MapLayerTemplate<Engine::IsoTiles>>(map_layer)->
		// 	set_tile_set(std::dynamic_pointer_cast<Engine::TileSetTemplate<Engine::IsoTiles>>(tile_set_from_factory));
		// map_layer->load_from_file("media/map/map_layer1.json");

		// while (!window->IsDone())
		// {
		// 	window->Update();
		// 	window->BeginDraw();
		// 	map_layer->draw();
			
		// 	window->EndDraw();
		// }
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
		layered_map.load_from_file("media/map/GameMap.json");

		while (!window->IsDone())
		{
			window->Update();
			window->BeginDraw();
			layered_map.draw();
			
			window->EndDraw();
		}
	}

	void test_animation()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);

		std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>(Engine::Configuration::textures.get(Engine::Configuration::Textures::Knigth2));
		std::shared_ptr<Engine::Animation> animation = std::make_shared<Engine::Animation>(texture->getSize());

		for (int i = 0; i < 9; i++)
		{
			animation->add_frame(sf::IntRect({64*i,200},{64,60}));
		}

		Engine::AnimatedSprite animated_sprite(*texture, animation, Engine::AnimatedSprite::Status::Playing);
		animated_sprite.play();

		animated_sprite.set_frame_time(sf::seconds(0.1f));
		animated_sprite.set_loop(true);
		animated_sprite.setScale({3.f,3.f});

		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time TimePerFrame = sf::seconds(1.f/60);

		while (!window->IsDone())
		{
			window->Update();
			bool repaint = false;
			timeSinceLastUpdate += clock.restart();

			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;
				animated_sprite.update(TimePerFrame);
			}

			if(repaint)
			{
				window->BeginDraw();
				window->Draw(animated_sprite);
				window->EndDraw();
			}
		}

		// sf::Time TimePerFrame = sf::seconds(1.f/60);
		// sf::Clock m_clock;
		// sf::Time timeSinceLastUpdate = sf::Time::Zero;
		// while (!window->IsDone())
		// {
		// 	window->Update();

		// 	// update

		// 	bool repaint = false;
		// 	timeSinceLastUpdate += m_clock.restart();

		// 	while (timeSinceLastUpdate > TimePerFrame)
		// 	{
		// 		timeSinceLastUpdate -= TimePerFrame;
		// 		repaint = true;
		// 		animated_sprite.update(timeSinceLastUpdate);
		// 	}

		// 	if(repaint)
		// 	{
		// 		window->BeginDraw();
		// 		// draw
		// 		window->Draw(animated_sprite);
		// 	}

		// 	window->EndDraw();

		// 	timeSinceLastUpdate += m_clock.restart();

		// 	float frametime = 1.0f / 60.0f;
		// 	if(timeSinceLastUpdate.asSeconds() >= frametime)
		// 	{
		// 		// Do something 60 times a second.
				
		// 		timeSinceLastUpdate -= sf::seconds(frametime); // Subtracting.
		// 	}
		// }
	}

	void test_animation2()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);

		Engine::SpriteSheetTemplate<Engine::KnightAnimations> sprite_sheet;

		sprite_sheet.LoadSheet<Engine::Anim_Directional>("media/Animations/Knight_Animations.json", Engine::Configuration::Textures::Knigth);
		sprite_sheet.SetAnimation(Engine::KnightAnimations::None);
		sprite_sheet.GetCurrentAnim()->Play();
		sprite_sheet.GetCurrentAnim()->SetLooping(true);
		sprite_sheet.SetSpriteScale({3.f,3.f});
		sprite_sheet.SetSpritePosition({100.f,100.f});

		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time TimePerFrame = sf::seconds(1.f/60);

		while (!window->IsDone())
		{
			window->Update();
			bool repaint = false;
			timeSinceLastUpdate += clock.restart();

			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;
				sprite_sheet.Update(TimePerFrame.asSeconds());
			}

			if(repaint)
			{
				window->BeginDraw();
				sprite_sheet.Draw(window->GetRenderWindow());
				// window->Draw();
				window->EndDraw();
			}
		}
	}
} // namespace Test
