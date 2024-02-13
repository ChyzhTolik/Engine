#include "LayeredMap.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "MapLayerTemplate.hpp"
#include "IsoTiles.hpp"

using nlohmann::json;

namespace Engine
{
    LayeredMap::LayeredMap(Engine::SharedContext& context): m_context(context)
    {

    }
        
    LayeredMap::~LayeredMap()
    {

    }

    void to_json(json& j, const EnemyPositionInfo& p) {
        j = json{ {"name", p.name}, {"coords", {p.coords.x, p.coords.y}} };
    }

    void from_json(const json& j, EnemyPositionInfo& p) {

        j.at("name").get_to(p.name);

        float coords[2];
        j.at("coords").get_to(coords);
        p.coords = sf::Vector2f(coords[0],coords[1]);
    }

    void to_json(json& j, const MapAdditionalInfo& p) {
        j = json
        {
            {"Warp", {p.warp.x, p.warp.y}},
            {"MapSize", {p.m_maxMapSize.x, p.m_maxMapSize.y}}, 
            {"Gravity", p.m_mapGravity},
            {"PlayerStartPos", {p.m_playerStart.x, p.m_playerStart.y}},
            {"NextMap", p.next_map},
            {"Friction", {p.friction.x, p.friction.y}},
            {"EnemyPositions", p.enemy_positions},
            {"LayersFiles",p.layers_files},
            {"TileSets",p.tile_set_files}
        };
    }

    void from_json(const json& j, MapAdditionalInfo& p) {

        j.at("Gravity").get_to(p.m_mapGravity);
        j.at("NextMap").get_to(p.next_map);

        unsigned int coords_u[2];
        j.at("Warp").get_to(coords_u);
        p.warp = sf::Vector2u(coords_u[0],coords_u[1]);

        j.at("MapSize").get_to(coords_u);
        p.m_maxMapSize = sf::Vector2u(coords_u[0],coords_u[1]);

        float coords_f[2];
        j.at("PlayerStartPos").get_to(coords_f);
        p.m_playerStart = sf::Vector2f(coords_f[0],coords_f[1]);

        j.at("Friction").get_to(coords_f);
        p.friction = sf::Vector2f(coords_f[0],coords_f[1]);

        j.at("EnemyPositions").get_to(p.enemy_positions);

        j.at("LayersFiles").get_to(p.layers_files);

        j.at("TileSets").get_to(p.tile_set_files);
    }

    void LayeredMap::load_from_file(const std::string& file_name)
    {
        std::fstream map_file{file_name};

        if (!map_file.good())
        { 
            std::cout << "! Failed loading " << file_name << "." << std::endl; return; 
        }

	    json jf = json::parse(map_file);
        m_map_info = jf;

        TileSetTemplate<IsoTiles> tile_set;
        tile_set.load_from_file("");

        for (const auto &i : m_map_info.layers_files)
        {
            std::shared_ptr<MapLayerInterface> layer = std::make_shared<MapLayerTemplate<IsoTiles>>(m_context);
            
        }
        
    }

    void LayeredMap::draw()
    {

    }

    void LayeredMap::add_layer(std::shared_ptr<MapLayerInterface> layer_map, int layer)
    {
        m_layered_map.emplace(layer, layer_map);
    }

    void LayeredMap::test_json()
    {
        // sf::Vector2u warp;
        // sf::Vector2u m_maxMapSize;
        // float m_mapGravity;
        // sf::Vector2f m_playerStart;
        // sf::Vector2f friction;
        // std::string next_map;
        std::vector<EnemyPositionInfo> enemy_positions{{"rat",{10.f,20.f}}};
        std::vector<std::string> layers_files{"map_layer1.json","map_layer2.json"};
        MapAdditionalInfo info{{0,1}, {100,200}, 0.6f, {23.f,23.f}, {0.f,0.5f},"empty",enemy_positions,layers_files};

        json j;
        j = info;

        MapAdditionalInfo info2 = j;

        std::cout<<j.dump()<<std::endl;

        std::fstream map_file{"media/map/map_info.json"};
        json jf = json::parse(map_file);
        MapAdditionalInfo map_info = jf;
    }
} // namespace Engine
