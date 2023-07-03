#pragma once
#include <SFML/Graphics.hpp>

#include "ResourceManager.hpp"
#include "ActionMap.hpp"

namespace Engine 
{
	class Configuration
	{
	public:
		Configuration() = delete;
		Configuration(const Configuration&) = delete;
		Configuration& operator=(const Configuration&) = delete;

		enum class Textures : int
		{
			Player,
			Tiles,
			Background,
			Biomenace,
			Intro,
			Mushroom,
		};

		static ResourceManager<sf::Texture, Textures> textures;

		enum class TetrisInputs
		{
			Down,
			Left,
			Right,
			Space,
			// Test
			I,Z,S,T,L,J,O,MouseL,MouseR
		};

		static ActionMap<TetrisInputs> tetris_inputs;

		enum class Musics
		{
			TakeItToTheTop,
		};

		static ResourceManager<sf::Music, Musics> musics;

		enum class Fonts
		{
			Arial,
		};

		static ResourceManager<sf::Font, Fonts> fonts;

		static void Initialize();
		static void clear();

	private:
		static void init_textures();
		static void init_tetris_inputs();
		static void init_musics();
		static void init_fonts();
	};
}

