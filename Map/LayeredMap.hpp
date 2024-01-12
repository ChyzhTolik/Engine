#pragma once

#include "TileSet.hpp"
#include "Vector2i_hash.hpp"
#include "SharedContext.hpp"

namespace NewMap
{
    struct MapTileInfo
    {
        uint32_t type;
        sf::Vector2i coords;
        int32_t layer;
        bool solid;
    };

    struct EnemyMapInfo
    {
        std::string name;
        sf::Vector2f coords;
    };

    struct MapAdditionalInfo
    {
        sf::Vector2u warp;
        sf::Vector2u m_maxMapSize;
        float m_mapGravity;
        sf::Vector2f m_playerStart;
        sf::Vector2f friction;
        std::string next_map;
    };

    using MapLayer = std::unordered_map<sf::Vector2i,std::shared_ptr<Tile>,Common::Vector2i_hash>;

    class LayeredMap
    {
    public:
        LayeredMap(Engine::SharedContext& context);
        ~LayeredMap();
        void set_tile_set(std::shared_ptr<TileSet> tile_set);
        void load_from_file(const std::string& file_name);
        void draw();
    private:
        Engine::SharedContext&  m_context;
        MapAdditionalInfo m_map_info;
        std::vector<EnemyMapInfo> m_enemyStarts;
        std::shared_ptr<TileSet> m_tile_set;
        std::map<int, MapLayer> m_layered_map;
        std::unordered_map<sf::Vector2i,std::shared_ptr<Tile>,Common::Vector2i_hash> m_map;
    };
    
} // namespace NewMap
