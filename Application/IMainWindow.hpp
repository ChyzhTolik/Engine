#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
	class IMainWindow
	{
	public:
		// Run the game
		void virtual run(int minimum_frames_per_second) = 0;

		// Manage all events from the user
		void virtual process_events() = 0;

		// Update the entire game
		void virtual update(sf::Time delta_time) = 0;

		// Manage all the rendering of the game
		void virtual render() = 0;
	};
}

