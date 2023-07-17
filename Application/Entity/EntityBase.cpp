#include "EntityBase.hpp"
#include "EntityManager.hpp"
#include "TileMap.hpp"
#include <cmath>
#include <optional>
#include <algorithm>

namespace Engine
{
    EntityBase::EntityBase(EntityManager& l_entityMgr)
        :m_entityManager(l_entityMgr), m_name("BaseEntity"),
        m_type(EntityType::Base), m_referenceTile(nullptr),
        m_state(EntityState::Idle), m_id(0),
        m_collidingOnX(false), m_collidingOnY(false)
    {

    }

    EntityBase::~EntityBase()
    {

    }

    void EntityBase::SetPosition(const float& l_x, const float& l_y)
    {
        m_position = sf::Vector2f(l_x,l_y);
        UpdateAABB();
    }
    
    void EntityBase::SetPosition(const sf::Vector2f& l_pos)
    {
        m_position = l_pos;
        UpdateAABB();
    }

    void EntityBase::SetSize(const float& l_x, const float& l_y)
    {
        m_size = sf::Vector2f(l_x,l_y);
        UpdateAABB();
    }

    void EntityBase::SetState(const EntityState& l_state)
    {
        if(m_state == EntityState::Dying){ return; }
        m_state = l_state;
    }

    const sf::Vector2f& EntityBase::GetSize()const
    { 
        return m_size; 
    }

    std::string EntityBase::GetName()const
    { 
        return m_name; 
    }

    EntityState EntityBase::GetState()const
    { 
        return m_state; 
    }

    unsigned int EntityBase::GetId()const
    { 
        return m_id; 
    }
    EntityType EntityBase::GetType()const
    { 
        return m_type; 
    }

    const sf::Vector2f& EntityBase::GetPosition()const
    { 
        return m_position; 
    }

    void EntityBase::Move(float l_x, float l_y)
    {
        m_positionOld = m_position;
        m_position += sf::Vector2f(l_x,l_y);

        sf::Vector2u mapSize = m_entityManager.GetContext().m_gameMap->GetMapSize();

        if(m_position.x < 0)
        {
            m_position.x = 0;
        } 
        else if(m_position.x > (mapSize.x + 1) * Sheet::Tile_Size)
        {
            m_position.x = (mapSize.x + 1) * Sheet::Tile_Size;
        }

        if(m_position.y < 0)
        {
            m_position.y = 0;
        }
        else if(m_position.y > (mapSize.y + 1) * Sheet::Tile_Size)
        {
            m_position.y = (mapSize.y + 1) * Sheet::Tile_Size;
            SetState(EntityState::Dying);
        }

        UpdateAABB();
    }

    void EntityBase::AddVelocity(float l_x, float l_y)
    {
        m_velocity += sf::Vector2f(l_x,l_y);

        if(abs(m_velocity.x) > m_maxVelocity.x)
        {
            if(m_velocity.x < 0)
            { 
                m_velocity.x = -m_maxVelocity.x; 
            }
            else 
            { 
                m_velocity.x = m_maxVelocity.x; 
            }
        }

        if(abs(m_velocity.y) > m_maxVelocity.y)
        {
            if(m_velocity.y < 0)
            { 
                m_velocity.y = -m_maxVelocity.y; 
            }
            else 
            { 
                m_velocity.y = m_maxVelocity.y; 
            }
        }
    }

    void EntityBase::Accelerate(float l_x, float l_y)
    {
        m_acceleration += sf::Vector2f(l_x,l_y);
    }

    void EntityBase::ApplyFriction(float l_x, float l_y)
    {
        if(m_velocity.x != 0)
        {
            if(abs(m_velocity.x) - abs(l_x) < 0)
            { 
                m_velocity.x = 0; 
            }
            else 
            {
                if(m_velocity.x < 0)
                { 
                    m_velocity.x += l_x; 
                }
                else 
                { 
                    m_velocity.x -= l_x; 
                }
            }
        }

        if(m_velocity.y != 0)
        {
            if (abs(m_velocity.y) - abs(l_y) < 0)
            { 
                m_velocity.y = 0; 
            }
            else 
            {
                if(m_velocity.y < 0)
                { 
                    m_velocity.y += l_y; 
                }
                else 
                { 
                    m_velocity.y -= l_y; 
                }
            }
        }
    }

    void EntityBase::Update(float l_dT)
    {
        std::shared_ptr<TileMap> map = m_entityManager.GetContext().m_gameMap;
        float gravity = map->GetGravity();
        Accelerate(0,gravity);
        AddVelocity(m_acceleration.x * l_dT, m_acceleration.y * l_dT);
        SetAcceleration(0.0f, 0.0f);
        sf::Vector2f frictionValue;

        if(m_referenceTile)
        {
            frictionValue = m_referenceTile->friction;

            if(m_referenceTile->is_deadly)
            { 
                SetState(EntityState::Dying); 
            }
        } 
        else if(map->GetDefaultTile())
        {
            frictionValue = map->GetDefaultTile()->friction;
        } 
        else 
        {
            frictionValue = m_friction;
        }

        float friction_x = (m_speed.x * frictionValue.x) * l_dT;
        float friction_y = (m_speed.y * frictionValue.y) * l_dT;
        ApplyFriction(friction_x, friction_y);
        sf::Vector2f deltaPos = m_velocity * l_dT;
        Move(deltaPos.x, deltaPos.y);
        m_collidingOnX = false;
        m_collidingOnY = false;
        CheckCollisions();
        ResolveCollisions();
    }

    bool SortCollisions(const CollisionElement& l_1,const CollisionElement& l_2)
    { 
        return l_1.m_area > l_2.m_area; 
    }

    void EntityBase::CheckCollisions()
    {
        std::shared_ptr<TileMap> gameMap = m_entityManager.GetContext().m_gameMap;
        unsigned int tileSize = gameMap->GetTileSize();
        int fromX = std::max(0.,floor(m_AABB.left / tileSize));
        int toX = floor((m_AABB.left + m_AABB.width) / tileSize);
        int fromY = std::max(0.,floor(m_AABB.top / tileSize));
        int toY = floor((m_AABB.top + m_AABB.height) / tileSize);

        for(int x = fromX; x <= toX; ++x)
        {
            for(int y = fromY; y <= toY; ++y)
            {
                auto tile = gameMap->GetTile(x,y);

                if (!tile)
                {
                    continue;
                }                

                sf::FloatRect tileBounds({x * tileSize*1.f, y * tileSize*1.f},
                {tileSize*1.f,tileSize*1.f});
                std::optional<sf::FloatRect> intersection;
                intersection = m_AABB.findIntersection(tileBounds);
                
                if (!intersection.has_value())
                {
                    continue;
                }
                
                float area = intersection.value().width * intersection.value().height;
                CollisionElement e(area, std::make_shared<TileInfo>(tile->m_tile_info), tileBounds);
                m_collisions.emplace_back(e);

                if(tile->m_warp && m_type == EntityType::Player)
                {
                    gameMap->LoadNext();
                }
            }
        }
    }

    void EntityBase::ResolveCollisions()
    {
        if(!m_collisions.empty())
        {
            std::sort(m_collisions.begin(),
            m_collisions.end(), SortCollisions);
            std::shared_ptr<TileMap> gameMap = m_entityManager.GetContext().m_gameMap;
            unsigned int tileSize = gameMap->GetTileSize();

            for (auto &itr : m_collisions)
            {
                if (!m_AABB.findIntersection(itr.m_tileBounds))
                { 
                    continue; 
                }

                float xDiff = (m_AABB.left + (m_AABB.width / 2)) - (itr.m_tileBounds.left + (itr.m_tileBounds.width / 2));
                float yDiff = (m_AABB.top + (m_AABB.height / 2)) - (itr.m_tileBounds.top + (itr.m_tileBounds.height / 2));
                float resolve = 0;

                if(abs(xDiff) > abs(yDiff))
                {
                    if(xDiff > 0)
                    {
                        resolve = (itr.m_tileBounds.left + tileSize) - m_AABB.left;
                    } 
                    else 
                    {
                        resolve = -((m_AABB.left + m_AABB.width) - itr.m_tileBounds.left);
                    }

                    Move(resolve, 0);
                    m_velocity.x = 0;
                    m_collidingOnX = true;
                } 
                else 
                {
                    if(yDiff > 0)
                    {
                        resolve = (itr.m_tileBounds.top + tileSize) - m_AABB.top;
                    } 
                    else 
                    {
                        resolve = - ((m_AABB.top + m_AABB.height) - itr.m_tileBounds.top);
                    }

                    Move(0,resolve);
                    m_velocity.y = 0;
                    if (m_collidingOnY){ continue; }
                    m_referenceTile = itr.m_tile;
                    m_collidingOnY = true;
                }
            }
            m_collisions.clear();
        }

        if(!m_collidingOnY)
        {
            m_referenceTile = nullptr; 
        }
    }

    void EntityBase::UpdateAABB()
    {
	    m_AABB = sf::FloatRect({m_position.x - (m_size.x / 2),m_position.y - m_size.y}, {m_size.x,m_size.y});
    }

    void EntityBase::SetAcceleration(float l_x, float l_y)
    {
        m_acceleration = sf::Vector2f(l_x,l_y);
    }
} // namespace Engine
