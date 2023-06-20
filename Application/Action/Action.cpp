#include "Action.hpp"

#include <cstring>

Engine::Action::Action(const Action& other) : m_type(other.m_type)
{
	std::memcpy(&m_event, &other.m_event, sizeof(sf::Event));
}

Engine::Action& Engine::Action::operator=(const Action& other)
{
	std::memcpy(&m_event, &other.m_event, sizeof(sf::Event));
	m_type = other.m_type;
	return *this;
}

Engine::Action::Action(const sf::Keyboard::Key& key, int type) : m_type(type)
{
	m_event.type = sf::Event::EventType::KeyPressed;
	m_event.key.code = key;
}

Engine::Action::Action(const sf::Mouse::Button& button, int type) : m_type(type)
{
	m_event.type = sf::Event::EventType::MouseButtonPressed;
	m_event.mouseButton.button = button;
}

bool Engine::Action::test() const
{
	bool result = false;

	if (m_event.type == sf::Event::EventType::KeyPressed)
	{
		if (m_type & to_int(Type::Pressed))
		{
			result = sf::Keyboard::isKeyPressed(m_event.key.code);
		}
	}
	else if (m_event.type == sf::Event::EventType::MouseButtonPressed)
	{
		if (m_type & to_int(Type::Pressed))
		{
			result = sf::Mouse::isButtonPressed(m_event.mouseButton.button);
		}
	}

	return result;
}

bool Engine::Action::operator==(const sf::Event& event) const
{
	bool result = false;

	switch (event.type)
	{
	case sf::Event::EventType::KeyPressed:
	{
		if (m_type & to_int(Type::Pressed) && m_event.type == sf::Event::EventType::KeyPressed)
		{
			result = event.key.code == m_event.key.code;
		}
	}
	break;
	case sf::Event::EventType::KeyReleased:
	{
		if (m_type & to_int(Type::Released) && m_event.type == sf::Event::EventType::KeyPressed)
		{
			result = event.key.code == m_event.key.code;
		}
	}
	break;
	case sf::Event::EventType::MouseButtonPressed:
	{
		if (m_type & to_int(Type::Pressed) && m_event.type == sf::Event::EventType::MouseButtonPressed)
		{
			result = event.mouseButton.button == m_event.mouseButton.button;
		}
	}
	break;
	case sf::Event::EventType::MouseButtonReleased:
	{
		if (m_type & to_int(Type::Released) && m_event.type == sf::Event::EventType::MouseButtonPressed)
		{
			result = event.mouseButton.button == m_event.mouseButton.button;
		}
	}
	break;
	default:
		break;
	}

	return result;
}

bool Engine::Action::operator==(const Action& other) const
{
	return m_type == other.m_type && other == m_event;
}
