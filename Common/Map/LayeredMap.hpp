#pragma once

#include "MapLayerInterface.hpp"
#include "Vector2i_hash.hpp"
#include "SharedContext.hpp"

namespace Engine
{
    struct EnemyPositionInfo
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
        std::vector<EnemyPositionInfo> enemy_positions;
        std::vector<std::string> layers_files;
        std::vector<std::string> tile_set_files;
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
        std::unordered_map<int, std::shared_ptr<MapLayerInterface>> m_layered_map;
    };
    
} // namespace NewMap
