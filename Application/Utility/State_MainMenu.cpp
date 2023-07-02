#include "State_MainMenu.hpp"
#include "StateManager.hpp"

namespace Engine
{
	MenuCreator::MenuCreator(
		StateManager& l_state_manager,
		const sf::Font& l_font) :
		StateCreator(l_state_manager), m_font(l_font)
	{
	}

	std::unique_ptr<BaseState> MenuCreator::create()
	{
		return std::make_unique<State_MainMenu>(m_state_manager, m_font);
	}

	State_MainMenu::State_MainMenu(StateManager& l_stateManager, const sf::Font& font) :
		BaseState(l_stateManager), m_text(font)
	{

	}


	State_MainMenu::~State_MainMenu()
	{
	}

	void State_MainMenu::OnCreate()
	{
		m_text.setString(sf::String("MAIN MENU:"));
		m_text.setCharacterSize(18);
		sf::FloatRect textRect = m_text.getLocalBounds();
		m_text.setOrigin({ textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f });
		m_text.setPosition({ 400, 100 });
		m_buttonSize = sf::Vector2f(300.0f, 32.0f);
		m_buttonPos = sf::Vector2f(400, 200);
		m_buttonPadding = 4; // 4px.
		std::string str[3];
		str[0] = "PLAY";
		str[1] = "CREDITS";
		str[2] = "EXIT";

		for (int i = 0; i < 3; ++i)
		{
			sf::Vector2f buttonPosition(m_buttonPos.x, m_buttonPos.y +
				(i * (m_buttonSize.y + m_buttonPadding)));
			m_rects[i].setSize(m_buttonSize);
			m_rects[i].setFillColor(sf::Color::Red);
			m_rects[i].setOrigin({ m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f });
			m_rects[i].setPosition(buttonPosition);

			sf::Text label(m_font);
			m_labels.emplace_back(std::move(label));
			m_labels.back().setString(sf::String(str[i]));
			m_labels.back().setCharacterSize(12);
			sf::FloatRect rect = m_labels.back().getLocalBounds();
			m_labels.back().setOrigin({ rect.left + rect.width / 2.0f,
				rect.top + rect.height / 2.0f });
			m_labels.back().setPosition(buttonPosition);
		}

		EventManager& evMgr = m_stateMgr.GetContext().m_eventManager;
		evMgr.add_action(StateType::MainMenu, "Mouse_Left", std::make_unique<MouseClickAction>(*this));
	}

	void State_MainMenu::OnDestroy()
	{
		m_stateMgr.GetContext().m_eventManager.remove_action(StateType::MainMenu, "Mouse_Left");
	}

	void State_MainMenu::Activate()
	{
		if (m_stateMgr.HasState(StateType::Game) && m_labels[0].getString() == "PLAY")
		{
			m_labels[0].setString(sf::String("RESUME"));
			sf::FloatRect rect = m_labels[0].getLocalBounds();
			m_labels[0].setOrigin({ rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f });
		}
	}

	void State_MainMenu::Deactivate()
	{
	}

	void State_MainMenu::Update(const sf::Time& l_time)
	{
	}

	void State_MainMenu::Draw()
	{
	}

	State_MainMenu::MouseClickAction::MouseClickAction(State_MainMenu& state) : m_state(state)
	{
	}

	void State_MainMenu::MouseClickAction::execute()
	{
	}
}

