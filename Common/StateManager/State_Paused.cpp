#include "State_Paused.hpp"
#include "StateManager.hpp"

namespace Engine
{
    PauseCreator::PauseCreator(StateManager& l_state_manager, const sf::Font& l_font) : StateCreator(l_state_manager), m_font(l_font)
    {

    }

    std::unique_ptr<BaseState> PauseCreator::create()
    {
        return std::make_unique<State_Paused>(m_state_manager, m_font);
    }

    State_Paused::State_Paused(StateManager& l_stateManager, const sf::Font& l_font) :
        BaseState(l_stateManager), m_text(l_font)
    {

    }

    State_Paused::~State_Paused()
    {

    }

    void State_Paused::OnCreate()
    {
        SetTransparent(true); // Set our transparency flag.
        m_text.setString(sf::String("PAUSED"));
        m_text.setCharacterSize(14);
        m_text.setStyle(sf::Text::Bold);
        sf::Vector2u windowSize = m_stateMgr.GetContext().m_wind->GetRenderWindow().getSize();
        sf::FloatRect textRect = m_text.getLocalBounds();
        m_text.setOrigin({textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f});
        m_text.setPosition({windowSize.x / 2.0f, windowSize.y / 2.0f});
        m_rect.setSize(sf::Vector2f(windowSize));
        m_rect.setPosition({0,0});
        m_rect.setFillColor(sf::Color(0,0,0,150));
        std::shared_ptr<EventManager> evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr->add_action(StateType::Paused,"Key_P",std::make_unique<UnpauseAction>(*this));
    }

    void State_Paused::OnDestroy()
    {
        std::shared_ptr<EventManager> evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr->remove_action(StateType::Paused,"Key_P");
    }

    void State_Paused::Draw()
    {
        sf::RenderWindow& wind = m_stateMgr.GetContext().m_wind->GetRenderWindow();
        wind.draw(m_rect);
        wind.draw(m_text);
    }

    State_Paused::UnpauseAction::UnpauseAction(State_Paused& state):m_state(state)
    {

    }

    void State_Paused::Activate()
    {

    }

    void State_Paused::Deactivate()
    {

    }

    void State_Paused::Update(const sf::Time& l_time) 
    {

    }

    void State_Paused::UnpauseAction::execute(EventDetails& l_details)
    {
        m_state.m_stateMgr.SwitchTo(StateType::Game);
    }
} // namespace Engine
