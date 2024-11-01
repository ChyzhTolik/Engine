#include "Player.hpp"
#include "EntityManager.hpp"
#include "StateManager.hpp"

namespace Engine
{
    Player::Player(EntityManager& l_entityMgr)
    : Character(l_entityMgr)
    {
        Load("media/Json/Knight_Char.json");
        m_type = EntityType::Player;
        std::shared_ptr<EventManager> events = m_entityManager.GetContext().m_eventManager;
        
        events->add_action(StateType::Game, "Player_MoveLeft", std::make_unique<MoveAction>(*this));
        events->add_action(StateType::Game, "Player_MoveRight", std::make_unique<MoveAction>(*this));
        events->add_action(StateType::Game, "Player_Jump", std::make_unique<JumpAction>(*this));
        events->add_action(StateType::Game, "Player_Attack", std::make_unique<AttackAction>(*this));
    }

    Player::~Player()
    {
        std::shared_ptr<EventManager>events = m_entityManager.GetContext().m_eventManager;        
        events->remove_action(StateType::Game,"Player_MoveLeft");
        events->remove_action(StateType::Game,"Player_MoveRight");
        events->remove_action(StateType::Game,"Player_Jump");
        events->remove_action(StateType::Game,"Player_Attack");
    }

    void Player::OnEntityCollision(EntityBase& l_collider, bool l_attack)
    {
        if (m_state == EntityState::Dying)
        { 
            return; 
        }

        if(l_attack)
        {
            if (m_state != EntityState::Attacking)
            { 
                return; 
            }

            if (!m_spriteSheet.GetCurrentAnim()->IsInAction())
            { 
                return; 
            }

            if (l_collider.GetType() != EntityType::Enemy && l_collider.GetType() != EntityType::Player)
            {
                return;
            }

            Character& opponent = (Character&)l_collider;
            opponent.GetHurt(1);

            if(m_position.x > opponent.GetPosition().x)
            {
                opponent.AddVelocity(-32,0);
            } 
            else 
            {
                opponent.AddVelocity(32,0);
            }
        } else 
        {
        // Other behavior.
        }
    }

    void Player::React(EventDetails& l_details)
    {
        if (l_details.m_name == "Player_MoveLeft")
        {
            Character::Move(Direction::Left);
        } 
        else if (l_details.m_name == "Player_MoveRight")
        {
            Character::Move(Direction::Right);
        } 
        else if (l_details.m_name == "Player_Jump")
        {
            Character::Jump();
        } 
        else if (l_details.m_name == "Player_Attack")
        {
            Character::Attack();
        }
    }

    Player::MoveAction::MoveAction(Player& l_entity) : m_entity(l_entity)
    {

    }

    void Player::MoveAction::execute(EventDetails& l_details)
    {
        if (l_details.m_name == "Player_MoveLeft")
        {
            m_entity.Move(Direction::Left);
        } 
        else if (l_details.m_name == "Player_MoveRight")
        {
            m_entity.Character::Move(Direction::Right);
        } 
    }

    Player::JumpAction::JumpAction(Player& l_entity) : m_entity(l_entity)
    {

    }

    void Player::JumpAction::execute(EventDetails& l_details)
    {
        m_entity.Character::Jump();
    }

    Player::AttackAction::AttackAction(Player& l_entity) : m_entity(l_entity)
    {

    }

    void Player::AttackAction::execute(EventDetails& l_details)
    {
        m_entity.Character::Attack();
    }

    PlayerCreator::PlayerCreator(EntityManager& l_entity_manager) : EntityCreator(l_entity_manager)
    {
        
    }

    std::shared_ptr<EntityBase> PlayerCreator::create()
    {
        return std::make_shared<Player>(m_entity_manager);
    }
} // namespace Engine
