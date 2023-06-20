#include "MainWindow.hpp"
#include <Configuration.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

Engine::MainWindow::MainWindow() : m_back(Configuration::textures.get(Configuration::Textures::Background))
{
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode({m_width, m_heigth}),"Tetris");
	m_player = std::make_unique<TestPlayer>();
	m_window->setKeyRepeatEnabled(false);
	init_gui();
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
		_sfgDesktop.HandleEvent(event);
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
	_sfgDesktop.Update(0.0);
    _sfgui.Display(*m_window);
	m_window->display();
}

void Engine::MainWindow::init_gui()
{
	auto title = sfg::Label::Create("Enter your starting level");
	auto level = sfg::Entry::Create();
	auto error = sfg::Label::Create();

	auto button = sfg::Button::Create( "Ok" );
	button->GetSignal( sfg::Button::OnLeftClick ).Connect(
	[level,error,this](){
		int lvl = 0;
		std::stringstream sstr(static_cast<std::string>(level->GetText()));
		sstr >> lvl;
		if(lvl < 1 or lvl > 100)
			error->SetText("Enter a number from 1 to 100.");
		else
		{
			error->SetText("");
		}
	});

	auto table = sfg::Table::Create();
	table->SetRowSpacings(10);
	table->Attach(title,sf::Rect<std::uint32_t>({0,0},{1,1}));
	table->Attach(level,sf::Rect<std::uint32_t>({0,1},{1,1}));
	table->Attach(button,sf::Rect<std::uint32_t>({0,2},{1,1}));
	table->Attach(error,sf::Rect<std::uint32_t>({0,3},{1,1}));
	table->SetAllocation(sf::FloatRect(
		{(m_window->getSize().x-300)/2.f,(m_window->getSize().y-200)/2.f},
		{300,200}
	));
	_sfgDesktop.Add(table);
}
