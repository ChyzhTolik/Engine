#pragma once
#include "TileSet.hpp"
#include <string_view>
#include "SharedContext.hpp"
#include "BaseState.hpp"

namespace Engine
{
    struct MapTileInfo
    {
        TileType type;
        sf::Vector2i coords;
    };

    struct EnemyMapInfo
    {
        std::string name;
        sf::Vector2f coords;
    };

    struct MapAdditionalInfo
    {
        sf::Vector2u m_maxMapSize;
        float m_mapGravity;
        sf::Vector2f m_playerStart;
        sf::Vector2f friction;
    };

    struct Vector2i_hash 
    {
        size_t operator()(const sf::Vector2u& p) const
        {
            auto hash1 = std::hash<unsigned int>{}(p.x);
            auto hash2 = std::hash<unsigned int>{}(p.y);
    
            if (hash1 != hash2) {
                return hash1 ^ hash2;             
            }
            
            // If hash1 == hash2, their XOR is zero.
            return hash1;
        }
    };

    class TileMap
    {
    private:
        TileSet m_tile_set;
        SharedContext&  m_context;
        std::unordered_map<sf::Vector2u,std::shared_ptr<Tile>,Vector2i_hash> m_map;
        sf::Vector2u m_maxMapSize;
        float m_mapGravity;
        TileInfo m_defaultTile;
        sf::Vector2f m_playerStart = {0,0};
        std::vector<EnemyMapInfo> m_enemyStarts;
        bool m_loadNextMap;
        std::string m_nextMap;
        std::shared_ptr<sf::Sprite> m_background;
    public:
        void load_from_file(std::string_view file);
        void draw();
        const sf::Vector2u& GetMapSize()const;
        float GetGravity()const;
        std::vector<EnemyMapInfo> get_enemy_positions()
        {
            return m_enemyStarts;
        }

        TileInfo* GetDefaultTile()
        { 
            return &m_defaultTile; 
        }
        unsigned int GetTileSize()const;
        std::shared_ptr<Tile> GetTile(unsigned int l_x, unsigned int l_y);
        const sf::Vector2f& GetPlayerStart() const;
        void LoadNext();
        void Update(float l_dT);
        void PurgeMap();

        TileMap(SharedContext& context);
        ~TileMap();
    };
} // namespace Engine
