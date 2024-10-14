#include "testing_libs.hpp"
#include "test_headers.hpp"


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

		sprite_sheet.load_sheet<Engine::Anim_Directional>("media/Animations/Knight_Animations.json", Engine::Configuration::Textures::Knigth);
		sprite_sheet.SetAnimation(Engine::KnightAnimations::None);
		sprite_sheet.GetCurrentAnim()->Play();
		sprite_sheet.GetCurrentAnim()->SetLooping(true);
		sprite_sheet.SetSpriteScale({3.f,3.f});
		sprite_sheet.SetSpritePosition({100.f,100.f});
		sprite_sheet.SetAnimation(Engine::AnimationsToStateConverter::convert(Engine::EntityState::Attacking));

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

	void test_character()
	{
		Engine::Configuration::Initialize();

		// Engine::Character char;
	}

	void test_entity_manager()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);

		std::shared_ptr<Engine::InfoBox> infobox = std::make_shared<Engine::InfoBox>();
		infobox->Setup(10,10,300,{320,0});

		Engine::SharedContext context;
		context.m_wind = window;
		context.m_eventManager = window->GetEventManager();
		context.m_info_box = infobox;

		std::shared_ptr<Engine::LayeredMap> map = std::make_shared<Engine::LayeredMap>(context);
		map->load_from_file("media/map/GameMap.json");
		context.m_game_map = map;

		Engine::EntityManager entity_manager(context);
		std::shared_ptr<Engine::StateManager> state_manager = std::make_shared<Engine::StateManager>(context);
		state_manager->SwitchTo(Engine::StateType::Game);

		entity_manager.Add(Engine::EntityType::Player, "Knight");
		auto entity = entity_manager.Find("Knight");
		std::shared_ptr<Engine::Player> player = std::dynamic_pointer_cast<Engine::Player>(entity);
		player->SetPosition({32,32});
		player->AddVelocity(0.f,200.0f);

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
				infobox->Clear();
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;
				entity_manager.Update(TimePerFrame.asSeconds());
			}

			if(repaint)
			{
				window->BeginDraw();
				map->draw();
				infobox->Render(window->GetRenderWindow());
				entity_manager.Draw();
				window->EndDraw();
			}
		}

		
	}

	void test_components()
	{
		Engine::PositionComponent pos_comp;
		Engine::PositionInfo pos_info{{1.3f,2.5f},6};

		json jey;
		jey = Engine::PosComponentTestHelper::get_json(pos_info);

		std::cout<<jey.dump(4)<<std::endl;
	}

	void test_new_entities()
	{
		std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
		Engine::EntitiesManager entities_manager(system_manager);
		Engine::ComponentBitSet mask;
		mask.set(static_cast<size_t>(Engine::ComponentType::Position));
		entities_manager.add_entity(mask);
	}

	void test_systems()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Knight Game", window_size);

		Engine::SharedContext context;
		context.m_wind = window;
		context.m_eventManager = window->GetEventManager();

		std::shared_ptr<Engine::InfoBox> infobox = std::make_shared<Engine::InfoBox>();
		infobox->Setup(10,10,300,{320,0});
		context.m_info_box = infobox;

		std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
		system_manager->fill_systems();
		std::shared_ptr<Engine::EntitiesManager> entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);
		auto id = entities_manager->add_entity("media/Entities/Knight_Char.json");
		entities_manager->set_player_id(id);
		system_manager->set_entity_manager(entities_manager);
		system_manager->set_infobox(infobox);

		auto sprite_sheet_component = 
        	entities_manager->get_component<Engine::SpriteSheetComponent<Engine::KnightAnimations>>(id, Engine::ComponentType::SpriteSheet);
		sprite_sheet_component->create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);
		auto sprite_sheet = std::dynamic_pointer_cast<Engine::SpriteSheetTemplate<Engine::KnightAnimations>>(sprite_sheet_component->get_sprite_sheet());
		sprite_sheet->SetAnimation(Engine::KnightAnimations::Idle);
		sprite_sheet->GetCurrentAnim()->Play();
		sprite_sheet->GetCurrentAnim()->SetLooping(true);
		sprite_sheet->SetDirection(Engine::Direction::Right);

		context.m_system_manager = system_manager;
		context.m_entities_manager = entities_manager;

		auto map = std::make_shared<Engine::LayeredMap>(context);
        map->load_from_file("media/map/GameMap2.json");
		context.m_game_map = map;

		std::shared_ptr<Engine::StateManager> state_manager = std::make_shared<Engine::StateManager>(context);
		state_manager->SwitchTo(Engine::StateType::Game);
		

		auto movement_component =
			entities_manager->get_component<Engine::MovableComponent>(id, Engine::ComponentType::Movable);

		auto position_component =
			entities_manager->get_component<Engine::PositionComponent>(id, Engine::ComponentType::Position);

		auto controller_component =
			entities_manager->get_component<Engine::ControllerComponent>(id, Engine::ComponentType::Controller);

		auto state_component =
			entities_manager->get_component<Engine::StateComponent>(id, Engine::ComponentType::State);

		auto collidable_component =
			entities_manager->get_component<Engine::CollidableComponent>(id, Engine::ComponentType::Collidable);

		auto jump_component =
			entities_manager->get_component<Engine::JumpComponent>(id, Engine::ComponentType::Jump);

		auto renderer_system = system_manager->get_system<Engine::RendererSystem>(Engine::SystemType::Renderer);
		auto movement_system = system_manager->get_system<Engine::MovementSystem>(Engine::SystemType::Movement);
		auto collidable_system = system_manager->get_system<Engine::CollisionSystem>(Engine::SystemType::Collision);
		auto controller_system = system_manager->get_system<Engine::ControllerSystem>(Engine::SystemType::Control);
		auto state_system = system_manager->get_system<Engine::StateSystem>(Engine::SystemType::State);
		auto sprite_sheet_system = system_manager->get_system<Engine::SpriteSheetSystem>(Engine::SystemType::SheetAnimation);
		auto jump_system = system_manager->get_system<Engine::JumpSystem>(Engine::SystemType::Jump);

		Engine::ChangeAnimationCallback callback = [&sprite_sheet](Engine::EntityState state, bool play, bool loop)
        {
            sprite_sheet->SetAnimation(Engine::AnimationsToStateConverter::convert(state), play, loop);
        };

        sprite_sheet_system->set_change_animation_callback(id, callback);

		movement_system->set_map(map);
		collidable_system->set_map(map);
		jump_system->set_map(map);

		collidable_component->set_origin(Engine::Origin::TopLeft);
		collidable_component->set_offset({0.f,0.f});

		state_manager->set_game_callback([&position_component]{
			position_component->set_position({160.f,64.f});
		});
		
		// movement_component->accelerate({0.f,map->get_gravity()});
		// movement_component->set_acceleration({10.f,10.f});
		// movement_component->set_speed({1024.f, 128.f});
		position_component->set_position({192.f,100.f});

		Engine::SpriteSheetTemplate<Engine::KnightAnimations> sprite_sheet2;

		sprite_sheet2.load_sheet<Engine::Anim_Directional>("media/Animations/Knight_Animations.json", Engine::Configuration::Textures::Knigth);
		sprite_sheet2.SetAnimation(Engine::KnightAnimations::None);
		sprite_sheet2.GetCurrentAnim()->Play();
		sprite_sheet2.GetCurrentAnim()->SetLooping(true);
		sprite_sheet2.SetSpritePosition({300.f,100.f});
		sprite_sheet2.SetAnimation(Engine::AnimationsToStateConverter::convert(Engine::EntityState::Idle));

		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Time TimePerFrame = sf::seconds(1.f/60);
		std::cout<<"thread id"<<std::this_thread::get_id()<<std::endl;
		while (!window->IsDone())
		{
			window->Update();
			bool repaint = false;
			timeSinceLastUpdate += clock.restart();

			while (timeSinceLastUpdate > TimePerFrame)
			{
				infobox->Clear();
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;
				system_manager->update(TimePerFrame.asSeconds());
				sprite_sheet2.Update(TimePerFrame.asSeconds());
			}

			if(repaint)
			{
				window->BeginDraw();
				system_manager->draw(window,0);
				infobox->Render(window->GetRenderWindow());
				map->draw();
				sprite_sheet2.Draw(window->GetRenderWindow());
				window->EndDraw();
			}
		}
	}

	void test_converter()
	{
		Engine::EntityState state {Engine::EntityState::Attacking};

		Engine::KnightAnimations animation = Engine::AnimationsToStateConverter::convert(state);
		
		state = Engine::EntityState::Dying;
		animation = Engine::AnimationsToStateConverter::convert(state);

	}

	void test_jumping()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Knight Game", window_size);

		Engine::SharedContext context;
		context.m_wind = window;
		context.m_eventManager = window->GetEventManager();

		auto map = std::make_shared<Engine::LayeredMap>(context);
        map->load_from_file("media/map/GameMap2.json");
		context.m_game_map = map;

		std::shared_ptr<Engine::StateManager> state_manager = std::make_shared<Engine::StateManager>(context);
		state_manager->SwitchTo(Engine::StateType::Game);

		sf::Texture hero_texture;
		auto res = hero_texture.loadFromFile("/home/achyzh/Projects/Engine/media/img/Hero Knight/Sprites/HeroKnight/Idle/HeroKnight_Idle_0.png");

		auto hero = std::make_unique<Test::Hero>(hero_texture);
		hero->init({300.f,300.f},200.f);

		state_manager->set_game_callback([&hero]{
			hero->jump(500.f);
		});

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
				hero->update(TimePerFrame.asSeconds());
				repaint = true;
			}

			if(repaint)
			{
				window->BeginDraw();
				map->draw();
				window->Draw(hero->get_sprite());
				window->EndDraw();
			}
		}
	}
} // namespace Test
