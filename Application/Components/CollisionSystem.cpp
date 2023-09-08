#include "CollisionSystem.hpp"

#include "Component.hpp"

namespace Engine
{
    CollisionSystem::CollisionSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::Collision, l_system_manager)
    {
        std::bitset<REQUIREMENTS_NUM> req;
        req.set((unsigned int)ComponentType::Position);
        req.set((unsigned int)ComponentType::Collidable);
        m_requiredComponents.push_back(req);

        m_gameMap = nullptr;
    }
    
    void CollisionSystem::SetMap(std::shared_ptr<TileMap> l_map)
    { 
        m_gameMap = l_map; 
    }

    CollisionSystem::~CollisionSystem()
    {
    }

    void CollisionSystem::Update(float l_dT)
    {
        if (!m_gameMap)
        { 
            return; 
        }

        auto entities = m_system_manager->GetEntityManager();

        for(auto &entity : m_entities)
        {
            auto position = entities->GetComponent<PositionComp>(entity, ComponentType::Position);
            auto collidable = entities->GetComponent<CollisionComponent>(entity, ComponentType::Collidable);
            collidable->SetPosition(position->get_position());
            collidable->ResetCollisionFlags();
            CheckOutOfBounds(position, collidable);
            MapCollisions(entity, position, collidable);
        }

        EntityCollisions();
    }

    void CollisionSystem::CheckOutOfBounds(std::shared_ptr<PositionComp> l_pos, std::shared_ptr<CollisionComponent> l_col)
    {
        unsigned int TileSize = m_gameMap->GetTileSize();

        if (l_pos->get_position().x < 0)
        {
            l_pos->set_position({0.0f, l_pos->get_position().y});
            l_col->SetPosition(l_pos->get_position());
        } 
        else if (l_pos->get_position().x > m_gameMap->GetMapSize().x * TileSize)
        {
            l_pos->set_position({m_gameMap->GetMapSize().x * TileSize * 1.f,l_pos->get_position().y});
            l_col->SetPosition(l_pos->get_position());
        }

        if (l_pos->get_position().y < 0)
        {
            l_pos->set_position({l_pos->get_position().x, 0.0f});
            l_col->SetPosition(l_pos->get_position());
        } 
        else if (l_pos->get_position().y > m_gameMap->GetMapSize().y * TileSize)
        {
            l_pos->set_position({l_pos->get_position().x,m_gameMap->GetMapSize().y * TileSize * 1.f});
            l_col->SetPosition(l_pos->get_position());
        }
    }

    void CollisionSystem::MapCollisions(const EntityId& l_entity, std::shared_ptr<PositionComp> l_pos, std::shared_ptr<CollisionComponent> l_col)
    {
        unsigned int TileSize = m_gameMap->GetTileSize();
        Collisions c;

        sf::FloatRect EntityAABB = l_col->GetCollidable();
        int FromX = floor(EntityAABB.left / TileSize);
        int ToX = floor((EntityAABB.left + EntityAABB.width) / TileSize);
        int FromY = floor(EntityAABB.top / TileSize);
        int ToY = floor((EntityAABB.top + EntityAABB.height) / TileSize);

        for (int x = FromX; x <= ToX; ++x){
            for (int y = FromY; y <= ToY; ++y){
                for (int l = 0; l < Sheet::NumLairs; ++l)
                {
                    std::shared_ptr<Tile> t = m_gameMap->get_tile_on_layer(x, y, l);

                    if (!t)
                    { 
                        continue;
                    }

                    if (!t->m_tile_info.m_solid)
                    { 
                        continue; 
                    }

                    sf::FloatRect TileAABB({x*TileSize*1.f, y*TileSize*1.f}, {TileSize*1.f, TileSize*1.f});

                    auto Intersection = EntityAABB.findIntersection(TileAABB);
                    float S = Intersection.value().width * Intersection.value().height;
                    c.emplace_back(S, std::make_shared<TileInfo>(t->m_tile_info), TileAABB);
                    break;
                }
            }
        }

        if (c.empty()){ return; }
        std::sort(c.begin(), c.end(), [](CollisionElement& l_1, CollisionElement& l_2){
            return l_1.m_area > l_2.m_area;
        });

        for (auto &col : c)
        {
            EntityAABB = l_col->GetCollidable();
            if (!EntityAABB.findIntersection(col.m_tileBounds))
            { 
                continue; 
            }

            float xDiff = (EntityAABB.left + (EntityAABB.width / 2)) - (col.m_tileBounds.left + (col.m_tileBounds.width / 2));
            float yDiff = (EntityAABB.top + (EntityAABB.height / 2)) - (col.m_tileBounds.top + (col.m_tileBounds.height / 2));
            float resolve = 0;
            if (std::abs(xDiff) > std::abs(yDiff)){
                if (xDiff > 0){
                    resolve = (col.m_tileBounds.left + TileSize) - EntityAABB.left;
                } else {
                    resolve = -((EntityAABB.left + EntityAABB.width) - col.m_tileBounds.left);
                }
                l_pos->MoveBy({resolve, 0});
                l_col->SetPosition(l_pos->get_position());
                m_system_manager->AddEvent(l_entity, (EventID)EntityEvent::Colliding_X);
                l_col->CollideOnX();
            } 
            else 
            {
                if (yDiff > 0){
                    resolve = (col.m_tileBounds.top + TileSize) - EntityAABB.top;
                } 
                else 
                {
                    resolve = -((EntityAABB.top + EntityAABB.height) - col.m_tileBounds.top);
                }

                l_pos->MoveBy({0, resolve});
                l_col->SetPosition(l_pos->get_position());
                m_system_manager->AddEvent(l_entity, (EventID)EntityEvent::Colliding_Y);
                l_col->CollideOnY();
            }
        }
    }

    void CollisionSystem::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event)
    {

    }

    void CollisionSystem::Notify(const Message& l_message)
    {

    }

    void CollisionSystem::EntityCollisions()
    {
        auto entities = m_system_manager->GetEntityManager();

        for(auto itr = m_entities.begin(); itr != m_entities.end(); ++itr)
        {
            for(auto itr2 = std::next(itr); itr2 != m_entities.end(); ++itr2)
            {
                auto collidable1 = entities->GetComponent<CollisionComponent>(*itr, ComponentType::Collidable);
                auto collidable2 = entities->GetComponent<CollisionComponent>(*itr2, ComponentType::Collidable);
                if(collidable1->GetCollidable().findIntersection(collidable2->GetCollidable()))
                {
                // Entity-on-entity collision!
                }
            }
        }
    }
} // namespace Engine
