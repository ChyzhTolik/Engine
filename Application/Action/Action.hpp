#pragma once
#include <SFML/Graphics.hpp>

namespace Engine
{
	class Action
	{
	public:
		enum class Type
		{
			RealTime = 1,
			Pressed = 1 << 1,
			Released = 1 << 2
		};

		Action(const Action& other);
		Action& operator=(const Action& other);

		Action(const sf::Keyboard::Key& key,
			int type = to_int(Type::RealTime) | to_int(Type::Pressed));

		Action(const sf::Mouse::Button& button,
			int type = to_int(Type::RealTime) | to_int(Type::Pressed));

		bool test() const;

		bool operator == (const sf::Event& event) const;
		bool operator == (const Action& other) const;

	private:
		inline static int to_int(Type type)
		{
			return static_cast<int>(type);
		}

		template<typename>
		friend class ActionTarget;
		sf::Event m_event;
		int m_type;
	};
}

