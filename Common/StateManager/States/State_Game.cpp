#include "State_Game.hpp"
#include "StateManager.hpp"
#include <iostream>
#include "Configuration.hpp"

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
        BaseState(l_stateManager), m_background_sprite(l_textrue)
    {
        
    }

    State_Game::~State_Game()
    {

    }

    void State_Game::OnCreate()
    {
        m_background_sprite.setOrigin
		(
			{
				m_background_sprite.getTextureRect().left + m_background_sprite.getTexture()->getSize().x / 2.f,
				m_background_sprite.getTextureRect().top + m_background_sprite.getTexture()->getSize().y / 2.f
			}
		);
        m_background_sprite.setScale({3.125f,4.17f});
        std::shared_ptr<EventManager> evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr->add_action(StateType::Game,"Key_P",std::make_unique<PauseAction>(*this));
        evMgr->add_action(StateType::Game,"Player_MoveRight",std::make_unique<MoveAction>(*this));
        evMgr->add_action(StateType::Game,"Player_MoveLeft",std::make_unique<MoveAction>(*this));
    }

    void State_Game::OnDestroy()
    {
        std::shared_ptr<EventManager> evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr->remove_action(StateType::Game,"Key_Escape");
        evMgr->remove_action(StateType::Game,"Key_P");
    }

    void State_Game::Update(const sf::Time& l_time)
    {
        auto context = m_stateMgr.GetContext();
        UpdateCamera();
    }

    void State_Game::Draw()
    {
        sf::Sprite sprite(Engine::Configuration::textures.get(Engine::Configuration::Textures::Background));
		m_stateMgr.GetContext().m_wind->Draw(sprite);
    }

    State_Game::ClickAction::ClickAction(State_Game& state) : m_state(state)
    {

    }

    void State_Game::ClickAction::execute(EventDetails& l_details)
    {
        
    }

    State_Game::MoveAction::MoveAction(State_Game& state) : m_state(state)
    {

    }

    void State_Game::MoveAction::execute(EventDetails& l_details)
    {
        Message msg(EntityMessage::Move);
        if (l_details.m_name == "Player_MoveLeft")
        {
            msg.m_data = Direction::Left;
        } 
        else if (l_details.m_name == "Player_MoveRight")
        {
            msg.m_data = Direction::Right;
        } 
        else if (l_details.m_name == "Player_MoveUp")
        {
            msg.m_data = Direction::Up;
        } 
        else if (l_details.m_name == "Player_MoveDown")
        {
            msg.m_data = Direction::Down;
        }

        msg.m_receiver = m_state.get_player_id();

        m_state.GetStateManager().GetContext().m_system_manager->get_message_handler()->dispatch(msg);
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

    void State_Game::UpdateCamera()
    {
        
    }

    void State_Game::set_player_id(const uint32_t id)
    {
        m_player = id;
    }

    uint32_t State_Game::get_player_id() const
    {
        return m_player;
    }
} // namespace Engine
