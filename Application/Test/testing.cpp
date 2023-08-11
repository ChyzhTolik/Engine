#include "testing.hpp"

#include "Engine_classes.hpp"

#include <iostream>
#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <memory>
#include "KnightTiles.hpp"



namespace Test
{
	void test()
	{
		std::cout << "Hello" << std::endl;
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

	void push_pair(std::vector<std::pair<sf::Vector2i, sf::Vector2i>>& vector,
		uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
	{
		vector.push_back(std::make_pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(left, top),
			sf::Vector2i(right - left, bottom - top)));
	}

	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> get_biomenace_run_frames()
	{
		std::vector<std::pair<sf::Vector2i, sf::Vector2i>> frames;
		push_pair(frames, 27, 49, 53, 89);
		push_pair(frames, 81, 49, 106, 89);
		push_pair(frames, 107, 49, 135, 89);
		push_pair(frames, 136, 49, 162, 89);
		push_pair(frames, 163, 49, 193, 89);

		return frames;
	}

	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> swap_frames(const std::vector<std::pair<sf::Vector2i, sf::Vector2i>>& frames)
	{
		std::vector<std::pair<sf::Vector2i, sf::Vector2i>> result;

		for (auto& frame : frames)
		{
			auto new_frame = frame;
			new_frame.first.x += frame.second.x;
			new_frame.second.x = -frame.second.x;
			result.push_back(new_frame);
		}

		return result;
	}

	int test_animation()
	{
		//Creation of the window
		sf::RenderWindow window(sf::VideoMode({ 600,800 }), "Example animation");
		//load of the texture image
		Engine::ResourceManager<sf::Texture, int> textures;
		Engine::TexturePtr texture = std::make_shared<sf::Texture>();
		if (!texture->loadFromFile("media/img/biomenace_complete.gif"))
		{
			return -1;
		}

		//textures.load(0, "media/img/eye.png");
		//Creation of the different animations
		std::shared_ptr<Engine::Animation> walkLeft = std::make_shared<Engine::Animation>(texture);

		//walkLeft->add_frames_line(4, 2, 0);
		std::shared_ptr<Engine::Animation> walkRight = std::make_shared<Engine::Animation>(texture);
		walkRight->add_frames_line(4, 2, 1);
		//Creation of the animates sprite
		Engine::AnimatedSprite sprite(walkLeft, Engine::AnimatedSprite::Status::Playing, sf::seconds(0.1f));
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

			float speed = 500; // the movement speed of the entity

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //move left
			{
				sprite.set_animation(walkLeft);
				sprite.play();
				sprite.move({ -speed * delta.asSeconds(),0 });
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				//move right
			{
				sprite.set_animation(walkRight);
				sprite.play();
				sprite.move({ speed * delta.asSeconds(),0 });
			}

			window.clear();
			sprite.update(delta); //update the animate sprite for possible frame change
			window.draw(sprite); //display the animation
			window.display();
		}
		return 0;
	}

	int test_biomenace()
	{
		Engine::Configuration::Initialize();
		//Creation of the window
		sf::RenderWindow window(sf::VideoMode({ 400,600 }), "Example animation");
		//load of the texture image
		/*std::string config_path = "/home/achyzh/TestProjects/Engine/Application/media/img/biomenace_complete.gif";
		if (!texture->loadFromFile(config_path))
		{
			return -1;
		}*/

		auto right_frames = get_biomenace_run_frames();

		const sf::Texture& conf_texture = Engine::Configuration::textures.get(Engine::Configuration::Textures::Biomenace);
		Engine::TexturePtr conf_text_ptr = std::make_shared < sf::Texture>(conf_texture);

		std::shared_ptr<Engine::Animation> walkLeft = std::make_shared<Engine::Animation>(conf_text_ptr);
		std::shared_ptr<Engine::Animation> walkRight = std::make_shared<Engine::Animation>(conf_text_ptr);

		for (auto& frame : right_frames)
		{
			walkRight->add_frame(sf::IntRect({ frame.first, frame.second }));
		}

		auto left_frames = swap_frames(right_frames);

		for (auto& frame : left_frames)
		{
			walkLeft->add_frame(sf::IntRect({ frame.first, frame.second }));
		}

		//Creation of the animates sprite
		Engine::AnimatedSprite animated_sprite(walkLeft, Engine::AnimatedSprite::Status::Playing, sf::seconds(0.1f));
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

			float speed = 500; // the movement speed of the entity

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //move left
			{
				animated_sprite.set_animation(walkLeft);
				animated_sprite.play();
				animated_sprite.move({ -speed * delta.asSeconds(),0 });
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				//move right
			{
				animated_sprite.set_animation(walkRight);
				animated_sprite.play();
				animated_sprite.move({ speed * delta.asSeconds(),0 });
			}

			window.clear();
			animated_sprite.update(delta); //update the animate sprite for possible frame change
			window.draw(animated_sprite); //display the animation
			window.display();
		}
		return 0;
	}

	int test_mushroom()
	{
		Engine::Configuration::Initialize();
		Engine::Game game;
		game.run(60);

		return 0;
	}

	sf::IntRect invert_horizontal(const sf::IntRect& rect)
    {
        sf::IntRect result = rect;
        result.left = rect.left + rect.width;
        result.width = -rect.width;

		return result;
    }

	void test_classes()
	{
		sf::Time m_elapsed = sf::Time::Zero;
		sf::Clock m_clock;
		sf::Time TimePerFrame = sf::seconds(1.f/60);
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);		

		Engine::SharedContext shared_context;
		shared_context.m_wind = window;
		shared_context.m_eventManager = window->GetEventManager();

		sf::View view = window->GetRenderWindow().getView();
		view.setCenter({300.f,600.f});

		window->GetRenderWindow().setView(view);
		
		std::shared_ptr<Engine::TileMap> map = std::make_shared<Engine::TileMap>(shared_context);
		shared_context.m_gameMap = map;
		map->load_from_file("media/Json/map.json");

		window->GetEventManager()->SetCurrentState(Engine::StateType::Game);

		sf::Sprite sprite(Engine::Configuration::textures.get(Engine::Configuration::Textures::Knigth));
		Engine::SpriteSheet sprite_sheet;
		sprite_sheet.LoadSheet("media/Json/Knight_Animations.json", 7);
		sprite_sheet.SetAnimation(Engine::AnimationType::Running);
		sprite_sheet.SetDirection(Engine::Direction::Right);
		auto animation = sprite_sheet.GetCurrentAnim();
		animation->SetLooping(true);
		animation->Play();
		sprite_sheet.SetSpritePosition({view.getCenter()});
		sprite_sheet.SetSpriteScale({3.f,3.f});

		Engine::EntityManager entity_manager(shared_context, 100);
		// entity_manager.Add(Engine::EntityType::Player);

		sf::Sprite background(Engine::Configuration::textures.get(Engine::Configuration::Textures::Background));
		background.setOrigin
		(
			{
				background.getTextureRect().left + background.getTexture()->getSize().x / 2.f,
				background.getTextureRect().top + background.getTexture()->getSize().y / 2.f
			}
		);
		
		background.setPosition(view.getCenter());
		background.setScale({3.125f,4.17f});

		Engine::Player player(entity_manager);

		sf::Sprite bio_sprite(Engine::Configuration::textures.get(Engine::Configuration::Textures::Biomenace));
		sf::IntRect rect_bio({27, 49}, {53-27, 89-49});
		sf::IntRect inv_rec({rect_bio.left+rect_bio.width,rect_bio.top},{-rect_bio.width,rect_bio.height});

		// sf::IntRect result;
        // result.left = rect.left + rect.width;
        // result.width = -rect.width;

		// return result;
		sf::IntRect inv_rec2 = invert_horizontal(rect_bio);
		bio_sprite.setTextureRect(inv_rec2);
		bio_sprite.setPosition({view.getCenter().x,view.getCenter().y - 100.f});
		bio_sprite.setScale({3.f,3.f});

		{
		// while(!window->IsDone())
        // {
        //     window->BeginDraw();
		// 	m_elapsed += m_clock.restart();

		// 	float frametime = 1.0f / 60.0f;
		// 	if(m_elapsed.asSeconds() >= frametime)
		// 	{				
		// 		m_elapsed -= sf::seconds(frametime); // Subtracting.
		// 	}

		// 	window->Update();
		// 	sprite_sheet.Update(m_elapsed.asSeconds());
		// 	// entity_manager.Update(m_elapsed.asSeconds());
		// 	map->Update(m_elapsed.asSeconds());
		// 	player.Update(m_elapsed.asSeconds());
		// 	view.setCenter(player.GetPosition());
		// 	window->GetRenderWindow().setView(view);
		// 	background.setPosition(view.getCenter());

		// 	m_elapsed = m_clock.restart();
		// 	// Render here.
		// 	window->Draw(background);
		// 	map->draw();
		// 	// sprite_sheet.Draw(window->GetRenderWindow());
		// 	// entity_manager.Draw();
		// 	player.Draw(window->GetRenderWindow());
		// 	window->EndDraw();
		// }
		}


		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (!window->IsDone())
		{
			window->Update();

			// update

			bool repaint = false;
			timeSinceLastUpdate += m_clock.restart();

			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;
				map->Update(TimePerFrame.asSeconds());
				sprite_sheet.Update(TimePerFrame.asSeconds());
				player.Update(TimePerFrame.asSeconds());
				view.setCenter(player.GetPosition());
				window->GetRenderWindow().setView(view);
				background.setPosition(view.getCenter());
			}

			if(repaint)
			{
				window->BeginDraw();
				// draw
				window->Draw(background);
				map->draw();
				sprite_sheet.Draw(window->GetRenderWindow());
				// entity_manager.Draw();
				player.Draw(window->GetRenderWindow());
				window->Draw(bio_sprite);
			}

			window->EndDraw();
		}
		
	}

	void test_sprite_origin()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);

		sf::CircleShape circle(30.f);
		sf::RectangleShape rectangle({50.f, 200.f});
		sf::RectangleShape rectangle2({50.f, 200.f});
		sf::RectangleShape back({200.f,200.f});
		rectangle.setFillColor(sf::Color::Cyan);
		rectangle.setPosition({100.f, 0.f});
		rectangle.setOrigin({0.f,0.f});
		rectangle2.setFillColor(sf::Color::Yellow);
		rectangle2.setPosition({50.f, 0.f});

		sf::Sprite sprite1(Engine::Configuration::textures.get(Engine::Configuration::Textures::Biomenace));
		sf::Sprite sprite2(Engine::Configuration::textures.get(Engine::Configuration::Textures::Biomenace));
		sf::IntRect sprite_rect({81, 48}, {106 - 81, 89 - 48});

		sf::Vector2f origin = {18.f, 0.f};

		sprite1.setTextureRect(sprite_rect);
		sprite1.setScale({2.f,2.f});
		sprite1.setOrigin(origin);
		sprite1.setPosition({100.f,0.f});

		auto invert_rect = invert_horizontal(sprite_rect);
		sprite2.setTextureRect(invert_rect);
		sprite2.setScale({2.f,2.f});
		sprite2.setOrigin({std::abs(sprite2.getTextureRect().width) - origin.x,0.f});
		sprite2.setPosition({100.f,100.f});

		std::cout<<sprite1.getTextureRect().width - origin.x<<std::endl;


		while (!window->IsDone())
		{
			window->Update();

			window->BeginDraw();

			window->Draw(back);
			window->Draw(rectangle);
			window->Draw(rectangle2);
			window->Draw(sprite1);
			window->Draw(sprite2);

			window->EndDraw();
		}	
	}

	void test_map()
	{
		Engine::Configuration::Initialize();
		sf::Vector2u window_size{800,600};
		std::shared_ptr<Engine::Window> window = std::make_shared<Engine::Window>("Test Window", window_size);

		sf::Sprite sprite(Engine::Configuration::textures.get(Engine::Configuration::Textures::Intro));
		sprite.setOrigin({sprite.getTextureRect().left + sprite.getTextureRect().width/2.f, sprite.getTextureRect().top + sprite.getTextureRect().height/2.f});
		sprite.setPosition({sprite.getTextureRect().width*1.f,sprite.getTextureRect().height*1.f});
		auto rect = sprite.getTextureRect();
		sf::RectangleShape rect_shape({rect.getSize().x*1.f,rect.getSize().y*1.f});
		auto rect_shape2 = rect_shape;
		rect_shape.setFillColor(sf::Color::Red);
		rect_shape2.setFillColor(sf::Color::Green);
		rect_shape.setOrigin({sprite.getTextureRect().left + sprite.getTextureRect().width/2.f, sprite.getTextureRect().top + sprite.getTextureRect().height/2.f});
		rect_shape.setPosition({sprite.getTextureRect().width*1.f,sprite.getTextureRect().height*1.f});


		NewMap::TileInfo tile_info{5,false,{0.8f,0.f},{0,0},{32,32}};
		NewMap::Tile tile(tile_info,6);
		tile.setPosition({400.f,300.f});

		NewMap::KnightTiles tile_type = tile.get_type<NewMap::KnightTiles>();
		tile_type = NewMap::KnightTiles::Icy_Rock;
		tile.set_type<NewMap::KnightTiles>(tile_type);
		std::cout<<static_cast<uint32_t>(tile_type)<<std::endl;

		NewMap::TileSet tile_set;
		tile_set.load_from_file("media/Json/IsometricTiles.json");
		auto tile1 = tile_set.get_tile(0);
		tile1->setPosition({100.f,100.f});

		while (!window->IsDone())
		{
			window->Update();

			window->BeginDraw(sf::Color::Black);

			// window->Draw(rect_shape);
			// window->Draw(rect_shape2);
			// window->Draw(sprite);
			window->Draw(tile);
			window->Draw(*tile1);

			window->EndDraw();
		}
	}
} // namespace Test