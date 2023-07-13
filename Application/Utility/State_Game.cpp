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
        BaseState(l_stateManager), m_background_sprite(l_textrue), m_map(std::make_shared<TileMap>(l_stateManager.GetContext()))
    {
        
    }

    State_Game::~State_Game()
    {

    }

    void State_Game::OnCreate()
    {
        m_background_sprite.setScale({3.125f,4.17f});
        std::shared_ptr<EventManager> evMgr = m_stateMgr.GetContext().m_eventManager;
        m_stateMgr.GetContext().m_gameMap = m_map;
        evMgr->add_action(StateType::Game,"Key_Escape",std::make_unique<MainMenuAction>(*this));
        evMgr->add_action(StateType::Game,"Key_P",std::make_unique<PauseAction>(*this));
        evMgr->add_action(StateType::Game,"Right",std::make_unique<MoveAction>(*this));
    }

    void State_Game::OnDestroy()
    {
        std::shared_ptr<EventManager> evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr->remove_action(StateType::Game,"Key_Escape");
        evMgr->remove_action(StateType::Game,"Key_P");
    }

    void State_Game::Update(const sf::Time& l_time)
    {
        SharedContext& context = m_stateMgr.GetContext();
        auto player = context.m_entityManager->Find("Knight");

        if(!player)
        {
            std::cout << "Respawning player..." << std::endl;
            context.m_entityManager->Add(EntityType::Player,"Knight");
            player = context.m_entityManager->Find("Knight");
            player->SetPosition(m_map->GetPlayerStart());
        }
        else 
        {
            m_view.setCenter(player->GetPosition());
            context.m_wind->GetRenderWindow().setView(m_view);
        }

        sf::FloatRect viewSpace = context.m_wind->GetViewSpace();

        if(viewSpace.left <= 0)
        {
            m_view.setCenter({viewSpace.width / 2,m_view.getCenter().y});
            context.m_wind->GetRenderWindow().setView(m_view);
        } 
        else if (viewSpace.left + viewSpace.width > (m_map->GetMapSize().x + 1) * Sheet::Tile_Size)
        {
            m_view.setCenter({((m_map->GetMapSize().x + 1) *
            Sheet::Tile_Size) - (viewSpace.width / 2),
            m_view.getCenter().y});
            context.m_wind->GetRenderWindow().setView(m_view);
        }
            m_map->Update(l_time.asSeconds());
            m_stateMgr.GetContext().m_entityManager->Update(l_time.asSeconds());
    }

    void State_Game::Draw()
    {
        m_stateMgr.GetContext().m_wind->GetRenderWindow().draw(m_background_sprite);
        m_map->draw();
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
        
    }
} // namespace Engine
