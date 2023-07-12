#include "Configuration.hpp"

namespace Engine
{
	ResourceManager<sf::Texture, Configuration::Textures> Configuration::textures;
	ActionMap<Configuration::TetrisInputs> Configuration::tetris_inputs;
	ResourceManager<sf::Music, Configuration::Musics> Configuration::musics;
	ResourceManager<sf::Font, Configuration::Fonts> Configuration::fonts;

	void Configuration::Initialize()
	{
		init_textures();
		init_tetris_inputs();
		init_musics();
		init_fonts();

		/*musics.get(Musics::TakeItToTheTop).setLoop(true);
		musics.get(Musics::TakeItToTheTop).play();*/
	}

	void Configuration::clear()
	{
		textures.clear();
	}

	void Configuration::init_textures()
	{
		textures.load(Textures::Player, "media/Player/Ship.png");
		textures.load(Textures::Tiles, "media/Player/tiles.png");
		textures.load(Textures::Background, "media/img/bg2.png");
		textures.load(Textures::Biomenace, "media/img/biomenace_complete.gif");
		textures.load(Textures::Intro, "media/img/intro.png");
		textures.load(Textures::Mushroom, "media/img/Mushroom.png");
		textures.load(Textures::TilesEngine, "media/SpriteSheets/tilesheet.png");
	}

	void Configuration::init_tetris_inputs()
	{
		tetris_inputs.map(TetrisInputs::Down, Action(sf::Keyboard::Down));
		tetris_inputs.map(TetrisInputs::Left, Action(sf::Keyboard::Left));
		tetris_inputs.map(TetrisInputs::Right, Action(sf::Keyboard::Right));
		tetris_inputs.map(TetrisInputs::Space, Action(sf::Keyboard::Space));
		// Test
		tetris_inputs.map(TetrisInputs::I, Action(sf::Keyboard::I));
		tetris_inputs.map(TetrisInputs::Z, Action(sf::Keyboard::Z));
		tetris_inputs.map(TetrisInputs::S, Action(sf::Keyboard::S));
		tetris_inputs.map(TetrisInputs::T, Action(sf::Keyboard::T));
		tetris_inputs.map(TetrisInputs::L, Action(sf::Keyboard::L));
		tetris_inputs.map(TetrisInputs::J, Action(sf::Keyboard::J));
		tetris_inputs.map(TetrisInputs::O, Action(sf::Keyboard::O));
		tetris_inputs.map(TetrisInputs::MouseL, Action(sf::Mouse::Button::Left));
		tetris_inputs.map(TetrisInputs::MouseR, Action(sf::Mouse::Button::Right));
	}

	void Configuration::init_musics()
	{
		musics.load(Musics::TakeItToTheTop, "media/music/take-it-to-the-top.ogg");
	}

	void Configuration::init_fonts()
	{
		fonts.load(Fonts::Arial, "media/fonts/arial.ttf");
	}
} // namespace Engine