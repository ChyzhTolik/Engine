#include "State_Game.hpp"
#include "StateManager.hpp"
#include <iostream>
#include "Configuration.hpp"
#include "PositionComp.hpp"
#include "MovementSystem.hpp"

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
        m_background_sprite.setOrigin
		(
			{
				m_background_sprite.getTextureRect().left + m_background_sprite.getTexture()->getSize().x / 2.f,
				m_background_sprite.getTextureRect().top + m_background_sprite.getTexture()->getSize().y / 2.f
			}
		);
        m_background_sprite.setScale({3.125f,4.17f});
        std::shared_ptr<EventManager> evMgr = m_stateMgr.GetContext().m_eventManager;
        m_stateMgr.GetContext().m_gameMap = m_map;
        evMgr->add_action(StateType::Game,"Key_Escape",std::make_unique<MainMenuAction>(*this));
        evMgr->add_action(StateType::Game,"Key_P",std::make_unique<PauseAction>(*this));
        evMgr->add_action(StateType::Game,"Right",std::make_unique<MoveAction>(*this));
        evMgr->add_action(StateType::Game, "Player_MoveLeft",std::make_unique<MoveAction>(*this));
        evMgr->add_action(StateType::Game, "Player_MoveRigth",std::make_unique<MoveAction>(*this));
        evMgr->add_action(StateType::Game, "Player_MoveUp",std::make_unique<MoveAction>(*this));
        evMgr->add_action(StateType::Game, "Player_MoveDown",std::make_unique<MoveAction>(*this));
        load_enemies();
        m_player = m_map->get_player_id();
        m_stateMgr.GetContext().m_system_manager->GetSystem<MovementSystem>(SystemType::Movement)->SetMap(m_map);
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
        m_map->Update(l_time.asSeconds());
        context.m_system_manager->Update(l_time.asSeconds());

        // SharedContext& context = m_stateMgr.GetContext();
        // auto player = context.m_entityManager->Find("Knight");

        // if(!player)
        // {
        //     std::cout << "Respawning player..." << std::endl;
        //     context.m_entityManager->Add(EntityType::Player,"Knight");
        //     player = context.m_entityManager->Find("Knight");
        //     player->SetPosition(m_map->GetPlayerStart());
        // }
        // else 
        // {
        //     m_view.setCenter(player->GetPosition());
        //     context.m_wind->GetRenderWindow().setView(m_view);
        // }

        // sf::FloatRect viewSpace = context.m_wind->GetViewSpace();

        // if(viewSpace.left <= 0)
        // {
        //     m_view.setCenter({viewSpace.width / 2,m_view.getCenter().y});
        //     context.m_wind->GetRenderWindow().setView(m_view);
        // } 
        // else if (viewSpace.left + viewSpace.width > (m_map->GetMapSize().x + 1) * Sheet::Tile_Size)
        // {
        //     m_view.setCenter({((m_map->GetMapSize().x + 1) *
        //     Sheet::Tile_Size) - (viewSpace.width / 2),
        //     m_view.getCenter().y});
        //     context.m_wind->GetRenderWindow().setView(m_view);
        // }
        
        // m_map->Update(l_time.asSeconds());
        // m_stateMgr.GetContext().m_entityManager->Update(l_time.asSeconds());
        // m_background_sprite.setPosition(m_view.getCenter());
    }

    void State_Game::Draw()
    {
        // m_stateMgr.GetContext().m_wind->GetRenderWindow().draw(m_background_sprite);
        // m_map->draw();
        // m_stateMgr.GetContext().m_entityManager->Draw();

        for(unsigned int i = 0; i < Sheet::NumLairs; ++i)
        {
            m_map->draw_layer(i);
            m_stateMgr.GetContext().m_system_manager->Draw(m_stateMgr.GetContext().m_wind, i);
        }
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
        Message msg((MessageType)EntityMessage::Move);

        if (l_details.m_name == "Player_MoveLeft")
        {
            msg.m_info = (int)Direction::Left;
        } 
        else if (l_details.m_name == "Player_MoveRight")
        {
        msg.m_info = (int)Direction::Right;
        } 
        else if (l_details.m_name == "Player_MoveUp")
        {
        msg.m_info = (int)Direction::Up;
        } 
        else if (l_details.m_name == "Player_MoveDown")
        {
            msg.m_info = (int)Direction::Down;
        }

        msg.m_receiver = m_state.m_player;
        m_state.m_stateMgr.GetContext().m_system_manager->GetMessageHandler().Dispatch(msg);
    }
    
    void State_Game::load_enemies()
    {
        SharedContext& context = m_stateMgr.GetContext();

        for (auto &&enemy : context.m_gameMap->get_enemy_positions())
        {
            int id = context.m_entityManager->Add(EntityType::Enemy,enemy.name);
            auto new_enemy = context.m_entityManager->Find(id);
            new_enemy->SetPosition(enemy.coords);
        }
    }

    void State_Game::UpdateCamera()
    {
        if (m_player == -1)
        { 
            return; 
        }

        auto context = m_stateMgr.GetContext();

        auto pos = m_stateMgr.GetContext().m_entities_manager->GetComponent<PositionComp>(m_player, ComponentType::Position);

        m_view.setCenter(pos->get_position());

        context.m_wind->GetRenderWindow().setView(m_view);

        sf::FloatRect viewSpace = context.m_wind->GetViewSpace();

        if (viewSpace.left <= 0)
        {
            m_view.setCenter({viewSpace.width / 2, m_view.getCenter().y});
            context.m_wind->GetRenderWindow().setView(m_view);
        } 
        else if (viewSpace.left + viewSpace.width >(m_map->GetMapSize().x) * Sheet::Tile_Size)
        {
            m_view.setCenter({((m_map->GetMapSize().x) * Sheet::Tile_Size) -
                (viewSpace.width / 2), m_view.getCenter().y});
            context.m_wind->GetRenderWindow().setView(m_view);
        }
        if (viewSpace.top <= 0)
        {
            m_view.setCenter({m_view.getCenter().x, viewSpace.height / 2});
            context.m_wind->GetRenderWindow().setView(m_view);
        } 
        else if (viewSpace.top + viewSpace.height > (m_map->GetMapSize().y) * Sheet::Tile_Size)
        {
            m_view.setCenter({m_view.getCenter().x,
                ((m_map->GetMapSize().y) * Sheet::Tile_Size) - (viewSpace.height / 2)});

            context.m_wind->GetRenderWindow().setView(m_view);
        }
    }
} // namespace Engine
