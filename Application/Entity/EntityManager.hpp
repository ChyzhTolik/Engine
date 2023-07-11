#pragma once

#include <unordered_map>
#include <functional>
#include "EntityBase.hpp"

namespace Engine
{
    class EntityManager;

    class EntityCreator // Functinoid
    {
    public:
        EntityCreator(EntityManager& l_entity_manager);
        virtual ~EntityCreator(){};
        virtual std::shared_ptr<EntityBase> create() = 0;
    protected:
        EntityManager& m_entity_manager;
    };

    using EntityContainer = std::unordered_map<unsigned int,std::shared_ptr<EntityBase>>;
    using EntityFactory = std::unordered_map< EntityType, std::unique_ptr<EntityCreator>>;
    using EnemyTypes = std::unordered_map<std::string,std::string>;
    struct SharedContext;

    class EntityManager
    {
    public:
        EntityManager(SharedContext& l_context, unsigned int l_maxEntities);
        ~EntityManager();
        int Add(const EntityType& l_type, const std::string& l_name = "");
        EntityBase& Find(unsigned int l_id);
        EntityBase& Find(const std::string& l_name);
        void Remove(unsigned int l_id);
        void Update(float l_dT);
        void Draw();
        void Purge();
        SharedContext& GetContext();

    private:
        template<typename T, typename ...Args>
        void RegisterEntity(const EntityType& l_type, Args&& ... args);
        // {
        //     m_entityFactory[l_type] = [this]() -> EntityBase*
        //     {
        //         return new T(*this);
        //     };
        // }

        void ProcessRemovals();
        void LoadEnemyTypes(const std::string& l_name);
        void EntityCollisionCheck();
        EntityContainer m_entities;
        EnemyTypes m_enemyTypes;
        EntityFactory m_entityFactory;
        SharedContext& m_context;
        unsigned int m_idCounter;
        unsigned int m_maxEntities;
        std::vector<unsigned int> m_entitiesToRemove;
    };

    template<typename T, typename ...Args>
    void EntityManager::RegisterEntity(const EntityType& l_type, Args&& ... args)
    {
        m_entityFactory.insert({l_type, std::make_shared<T>(*this, std::forward<Args>(args)...)});
    }
} // namespace Engine
