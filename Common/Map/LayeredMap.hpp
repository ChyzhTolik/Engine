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
        bool is_solid;
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
        int main_layer_position;
    };

    class LayeredMap
    {
    public:
        LayeredMap(Engine::SharedContext& context);
        ~LayeredMap();
        void load_from_file(const std::string& file_name);
        void draw();
        size_t layers_count() const;
        sf::Vector2u get_map_size() const;
        sf::Vector2u get_tile_size() const;
        float get_gravity() const;
        sf::Vector2f get_default_friction() const;
        std::shared_ptr<Tile> get_tile(int32_t layer, const sf::Vector2i& coords) const;
        sf::Vector2u get_warp_coords() const;
        void load_next_map();
        int get_main_layer_index() const;
        bool is_solid(int32_t layer) const;
    private:
        Engine::SharedContext&  m_context;
        MapAdditionalInfo m_map_info;
        std::map<int16_t, std::shared_ptr<MapLayerInterface>> m_layers;
        std::shared_ptr<MapLayerInterface> m_main_layer;
        sf::Vector2f m_default_friction;
        sf::Vector2u m_warp_coords;
    };
    
} // namespace NewMap
