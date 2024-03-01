#include "Configuration.hpp"

namespace Engine
{
	ResourceManager<sf::Texture, Configuration::Textures> Configuration::textures;
	ResourceManager<sf::Music, Configuration::Musics> Configuration::musics;
	ResourceManager<sf::Font, Configuration::Fonts> Configuration::fonts;

	void Configuration::Initialize()
	{
		init_textures();
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
		textures.load(Textures::Biomenace, "media/SpriteSheets/BiomenaceSheet.gif");
		textures.load(Textures::Intro, "media/img/intro.png");
		textures.load(Textures::Mushroom, "media/img/Mushroom.png");
		textures.load(Textures::TilesEngine, "media/SpriteSheets/tilesheet.png");
		textures.load(Textures::Knigth, "media/SpriteSheets/KnigthSheet.png");
		textures.load(Textures::Rat, "media/SpriteSheets/RatSheet.png");
		textures.load(Textures::IsometricTiles,"media/SpriteSheets/tilesheet2.png");
		textures.load(Textures::Knigth2,"media/SpriteSheets/BODY_male_Epic_armors_Golden.png");
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