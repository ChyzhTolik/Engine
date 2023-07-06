#include "State_Game.hpp"
#include "StateManager.hpp"

namespace Engine
{
    GameCreator::GameCreator(StateManager& l_state_manager, const sf::Texture& l_texture):
        StateCreator(l_state_manager), m_texture(l_texture)
    {

    }

    std::unique_ptr<BaseState> GameCreator::create()
    {
        return std::make_unique<State_Game>(m_state_manager, m_texture);
    }

    State_Game::State_Game(StateManager& l_stateManager, const sf::Texture& l_textrue):
        BaseState(l_stateManager), m_background_sprite(l_textrue), m_map(l_stateManager.GetContext())
    {
        m_background_sprite.setScale({3.125f,4.17f});
        m_sprite_sheet.LoadSheet("media/Player.json");
        m_sprite_sheet.SetAnimation(AnimationType::Idle);
        m_sprite_sheet.SetSpritePosition({30.f, 450.f});
        m_sprite_sheet.SetSpriteScale({3.f,3.f});
        auto animation = m_sprite_sheet.GetCurrentAnim();
        animation->SetLooping(true);
        animation->Play();
    }

    State_Game::~State_Game()
    {

    }

    void State_Game::OnCreate()
    {
        m_background_sprite.setPosition({0,0});
        m_increment = sf::Vector2f(400.0f,400.0f);
        EventManager& evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr.add_action(StateType::Game,"Key_Escape",std::make_unique<MainMenuAction>(*this));
        evMgr.add_action(StateType::Game,"Key_P",std::make_unique<PauseAction>(*this));
        evMgr.add_action(StateType::Game,"Right",std::make_unique<MoveAction>(*this));
    }

    void State_Game::OnDestroy()
    {
        EventManager& evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr.remove_action(StateType::Game,"Key_Escape");
        evMgr.remove_action(StateType::Game,"Key_P");
    }

    void State_Game::Update(const sf::Time& l_time)
    {
        m_sprite_sheet.Update(l_time.asSeconds());

    }

    void State_Game::Draw()
    {
        m_stateMgr.GetContext().m_wind.GetRenderWindow().draw(m_background_sprite);
        m_sprite_sheet.Draw(m_stateMgr.GetContext().m_wind.GetRenderWindow());
        // m_map.draw();
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

    State_Game::MoveAction::MoveAction(State_Game& state): m_state(state)
    {

    }

    void State_Game::MoveAction::execute(EventDetails& l_details)
    {
        m_state.m_sprite_sheet.SetAnimation(AnimationType::Running);
        auto animation = m_state.m_sprite_sheet.GetCurrentAnim();
        animation->SetLooping(true);
        animation->Play();
    }
} // namespace Engine
