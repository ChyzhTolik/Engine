#pragma once

#include <map>

#include "MapLayerInterface.hpp"
#include "Vector2i_hash.hpp"
#include "SharedContext.hpp"
#include "TileSetInterface.hpp"
#include "MapLayerInterface.hpp"
#include "MapStructs.hpp"

namespace Engine
{
    struct MapSize
    {
        uint32_t width;
        uint32_t height;
    };

    struct MapLayerInfo
    {
        std::string tile_set_name;
        std::string file;
        int16_t position;
    };

    struct EnemyPositionInfo
    {
        std::string name;
        sf::Vector2f coords;
    };

    struct MapAdditionalInfo
    {
        sf::Vector2u warp;
        MapSize m_maxMapSize;
        float m_mapGravity;
        sf::Vector2f m_playerStart;
        sf::Vector2f friction;
        std::string next_map;
        std::vector<EnemyPositionInfo> enemy_positions;
        std::vector<MapTileSetInfo> tile_sets;
        std::vector<MapLayerInfo> layers;
        std::string jsons_path;
    };

    class LayeredMap
    {
    public:
        LayeredMap(Engine::SharedContext& context);
        ~LayeredMap();
        void load_from_file(const std::string& file_name);
        void draw();
        void add_layer(std::shared_ptr<MapLayerInterface> layer_map, int layer);
        void test_json();
    private:
        Engine::SharedContext&  m_context;
        MapAdditionalInfo m_map_info;
        std::map<int16_t, std::shared_ptr<MapLayerInterface>> m_layers;
    };
    
} // namespace NewMap
