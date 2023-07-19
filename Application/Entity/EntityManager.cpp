#include "EntityManager.hpp"
#include "SharedContext.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Engine
{
    EntityManager::EntityManager(SharedContext& l_context, unsigned int l_maxEntities):
        m_context(l_context),
        m_maxEntities(l_maxEntities), 
        m_idCounter(0)
    {
        LoadEnemyTypes("media/Json/EnemyList.json");
        RegisterEntity<PlayerCreator>(EntityType::Player);
        RegisterEntity<EnemyCreator>(EntityType::Enemy);
    }

    EntityManager::~EntityManager()
    { 
        Purge(); 
    }

    int EntityManager::Add(const EntityType& l_type,const std::string& l_name)
    {
        auto itr = m_entityFactory.find(l_type);

        if (itr == m_entityFactory.end())
        { 
            return -1; 
        }

        auto entity = itr->second->create();
        entity->m_id = m_idCounter;

        if (l_name != "")
        { 
            entity->m_name = l_name; 
        }

        m_entities.emplace(m_idCounter,std::move(entity));

        if(l_type == EntityType::Enemy)
        {
            auto itr = m_enemyTypes.find(l_name);
            
            if(itr != m_enemyTypes.end()){
                Enemy& enemy = static_cast<Enemy&>(*entity);
                enemy.Load(itr->second);
            }
        }

        ++m_idCounter;
        return m_idCounter - 1;
    }

    std::shared_ptr<EntityBase> EntityManager::Find(const std::string& l_name)
    {
        for(auto &itr : m_entities)
        {
            if(itr.second->GetName() == l_name){
                return itr.second;
            }
        }

        return nullptr;
    }

    std::shared_ptr<EntityBase> EntityManager::Find(unsigned int l_id)
    {
        auto itr = m_entities.find(l_id);

        if (itr == m_entities.end())
        { 
            return nullptr; 
        }

        return itr->second;
    }

    void EntityManager::Update(float l_dT)
    {
        for(auto &itr : m_entities)
        {
            itr.second->Update(l_dT);
        }

        EntityCollisionCheck();
        ProcessRemovals();
    }

    void EntityManager::Draw()
    {
        sf::RenderWindow& wnd = m_context.m_wind->GetRenderWindow();
        sf::FloatRect viewSpace = m_context.m_wind->GetViewSpace();

        for(auto &itr : m_entities)
        {
            if (!viewSpace.findIntersection(itr.second->m_AABB))
            { 
                continue; 
            }

            itr.second->Draw(wnd);
        }
    }

    void EntityManager::Purge()
    {
        m_entities.clear();
        m_idCounter = 0;
    }

    void EntityManager::ProcessRemovals()
    {
        while(m_entitiesToRemove.begin() != m_entitiesToRemove.end())
        {
            unsigned int id = m_entitiesToRemove.back();
            auto itr = m_entities.find(id);

            if(itr != m_entities.end())
            {
                std::cout << "Discarding entity: " << itr->second->GetId() << std::endl;
                m_entities.erase(itr);
            }
            m_entitiesToRemove.pop_back();
        }
    }

    void EntityManager::EntityCollisionCheck()
    {
        if (m_entities.empty())
        { 
            return; 
        }

        for(auto itr = m_entities.begin(); std::next(itr) != m_entities.end(); ++itr)
        {
            for(auto itr2 = std::next(itr); itr2 != m_entities.end(); ++itr2)
            {
                if(itr->first == itr2->first)
                { 
                    continue; 
                }

                // Regular AABB bounding box collision.
                if(itr->second->m_AABB.findIntersection(itr2->second->m_AABB))
                {
                    itr->second->OnEntityCollision(*(itr2->second), false);
                    itr2->second->OnEntityCollision(*(itr->second), false);
                }

                EntityType t1 = itr->second->GetType();
                EntityType t2 = itr2->second->GetType();

                if (t1 == EntityType::Player || t1 == EntityType::Enemy)
                {
                    Character& c1 = static_cast<Character&>(*itr->second);

                    if (c1.m_attackAABB.findIntersection(itr2->second->m_AABB))
                    {
                        c1.OnEntityCollision(*(itr2->second), true);
                    }
                }

                if (t2 == EntityType::Player || t2 == EntityType::Enemy)
                {
                    Character& c2 = static_cast<Character&>(*itr2->second);

                    if (c2.m_attackAABB.findIntersection(itr->second->m_AABB))
                    {
                        c2.OnEntityCollision(*(itr->second), true);
                    }
                }
            }
        }
    }

    void to_json(json& j, const EnemyInfo& p)
    {
        j = json
        { 
            {"Name", p.name},
            {"File", p.file},
        };
    }

    void from_json(const json& j, EnemyInfo& p) 
    {
        j.at("Name").get_to(p.name);
        j.at("File").get_to(p.file);
    }

    void EntityManager::LoadEnemyTypes(const std::string& l_name)
    {
        std::ifstream inFile { l_name };

        if (!inFile.good()) 
        {
            std::cout << "! Failed loading "<<l_name<<"." << std::endl; 
            return; 
        }

        json jf = json::parse(inFile);
        std::vector<EnemyInfo> enemies = jf;

        for (auto &&enemy : enemies)
        {
            m_enemyTypes.insert({std::move(enemy.name), std::move(enemy.file)});
        }        
    }

    SharedContext& EntityManager::GetContext()
    {
        return m_context;
    }

    void EntityManager::Remove(unsigned int l_id)
    {
        m_entities.erase(l_id);
    }

    EntityCreator::EntityCreator(EntityManager& l_entity_manager) : m_entity_manager(l_entity_manager)
    {

    }
} // namespace Engine
