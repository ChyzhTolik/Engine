#include "MainWindow.hpp"
#include <Configuration.hpp>

Engine::MainWindow::MainWindow() : m_back(Configuration::textures.get(Configuration::Textures::Background))
{
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode({m_width, m_heigth}),"Tetris");
	m_player = std::make_unique<TestPlayer>();
	m_window->setKeyRepeatEnabled(false);
}

Engine::MainWindow::~MainWindow()
{
}

void Engine::MainWindow::run(int minimum_frames_per_second)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / minimum_frames_per_second);

	while (m_window->isOpen())
	{
		process_events();

		bool repaint = false;

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}

		//update(timeSinceLastUpdate);

		render();
	}
}

void Engine::MainWindow::process_events()
{
	sf::Event event;

	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed
			|| (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			m_window->close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P && !m_pause_key_state)
			{
				m_is_paused=!m_is_paused;
			}

			m_pause_key_state = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			m_pause_key_state = false;
		}

		m_player->process_events();
	}
}

void Engine::MainWindow::update(sf::Time delta_time)
{
	if (m_is_paused)
	{
		return;
	}

	m_player->update(delta_time);
}

void Engine::MainWindow::render()
{
	m_window->clear();
	m_window->draw(m_back);
	m_window->draw(*m_player);
	m_window->display();
}
