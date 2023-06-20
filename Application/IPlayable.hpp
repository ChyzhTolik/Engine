#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
	class IPlayable
	{
	public:
		void virtual update(sf::Time delta_time) = 0;
		void virtual process_events() = 0;
	};
}
