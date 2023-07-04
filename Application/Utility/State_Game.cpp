#include "State_Game.hpp"
#include "StateManager.hpp"

namespace Engine
{
    GameCreator::GameCreator(StateManager& l_state_manager, const sf::Texture& l_texture):
        StateCreator(l_state_manager), m_texture(l_texture)
    {

    }

    GameCreator::GameCreator(StateManager& l_state_manager, const sf::Sprite& l_sprite) :
        StateCreator(l_state_manager), m_sprite(std::make_shared<sf::Sprite>(l_sprite)), m_texture(*(l_sprite.getTexture()))
    {

    }

    std::unique_ptr<BaseState> GameCreator::create()
    {
        return std::make_unique<State_Game>(m_state_manager, *m_sprite);
    }

    State_Game::State_Game(StateManager& l_stateManager, const sf::Texture& l_textrue):
        BaseState(l_stateManager), m_game_sprite(l_textrue), m_map(l_stateManager.GetContext())
    {
        
    }

    State_Game::State_Game(StateManager& l_stateManager, const sf::Sprite& l_sprite):
        BaseState(l_stateManager), m_game_sprite(l_sprite), m_map(l_stateManager.GetContext())
    {

    }

    State_Game::~State_Game()
    {

    }

    void State_Game::OnCreate()
    {
        m_game_sprite.setPosition({0,0});
        m_increment = sf::Vector2f(400.0f,400.0f);
        EventManager& evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr.add_action(StateType::Game,"Key_Escape",std::make_unique<MainMenuAction>(*this));
        evMgr.add_action(StateType::Game,"Key_P",std::make_unique<PauseAction>(*this));
    }

    void State_Game::OnDestroy()
    {
        EventManager& evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr.remove_action(StateType::Game,"Key_Escape");
        evMgr.remove_action(StateType::Game,"Key_P");
    }

    void State_Game::Update(const sf::Time& l_time)
    {
        // sf::Vector2u l_windSize = m_stateMgr.GetContext().m_wind.GetWindowSize();
        // sf::Vector2u l_textSize = m_game_sprite.getTexture()->getSize();

        // if((m_game_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
        //     (m_game_sprite.getPosition().x < 0 && m_increment.x < 0))
        // {
        //     m_increment.x = -m_increment.x;
        // }

        // if((m_game_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
        //     (m_game_sprite.getPosition().y < 0 && m_increment.y < 0))
        // {
        //     m_increment.y = -m_increment.y;
        // }

        // m_game_sprite.setPosition({m_game_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()),
        //     m_game_sprite.getPosition().y + (m_increment.y * l_time.asSeconds())});
    }

    void State_Game::Draw()
    {
        // m_stateMgr.GetContext().m_wind.GetRenderWindow().draw(m_game_sprite);
        m_map.draw();
    }

    State_Game::MainMenuAction::MainMenuAction(State_Game& state) : m_state(state)
    {

    }

    void State_Game::MainMenuAction::execute(EventDetails& l_details)
    {
        m_state.m_stateMgr.SwitchTo(StateType::MainMenu);
    }

    State_Game::PauseAction::PauseAction(State_Game& state) : m_state(state)
    {

    }

    void State_Game::PauseAction::execute(EventDetails& l_details)
    {
        m_state.m_stateMgr.SwitchTo(StateType::Paused);
    }

    void State_Game::Activate(){};
    void State_Game::Deactivate(){};
} // namespace Engine
