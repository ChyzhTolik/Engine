#include "LayeredMap.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using nlohmann::json;

namespace NewMap
{
    LayeredMap::LayeredMap(Engine::SharedContext& context) : m_context(context)
    {
    }
    
    LayeredMap::~LayeredMap()
    {
    }

    void to_json(json& j, const MapTileInfo& p) 
    {
        j = json
        { 
            {"type", p.type}, 
            {"coords", {p.coords.x, p.coords.y}},
            {"layer", p.layer},
            {"solid", static_cast<int>(p.solid)} 
        };
    }

    void from_json(const json& j, MapTileInfo& p) 
    {

        j.at("type").get_to(p.type);
        j.at("layer").get_to(p.layer);

        int solid;
        j.at("solid").get_to(solid);
        p.solid = static_cast<bool>(solid);

        int coords[2];
        j.at("coords").get_to(coords);
        p.coords = sf::Vector2i(coords[0],coords[1]);
    }

    void to_json(json& j, const MapAdditionalInfo& p) {
        j = json{
            {"Warp", {p.warp.x, p.warp.y}},
            {"MapSize", {p.m_maxMapSize.x, p.m_maxMapSize.y}}, 
            {"Gravity", p.m_mapGravity},
            {"PlayerStartPos", {p.m_playerStart.x, p.m_playerStart.y}},
            {"NextMap", p.next_map},
            {"Friction", {p.friction.x, p.friction.y}}
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
    }

    void to_json(json& j, const EnemyMapInfo& p) {
        j = json{ {"name", p.name}, {"coords", {p.coords.x, p.coords.y}} };
    }

    void from_json(const json& j, EnemyMapInfo& p) {

        j.at("name").get_to(p.name);

        float coords[2];
        j.at("coords").get_to(coords);
        p.coords = sf::Vector2f(coords[0],coords[1]);
    }

    void LayeredMap::load_from_file(const std::string& file_name)
    {
        std::ifstream tiles(file_name);

        if (!tiles.good())
        {
            std::cout << "! Failed loading "<<file_name<<"." << std::endl; 
            return; 
        }
        
        json jf = json::parse(tiles);
        std::vector<MapTileInfo> key_infos;

        m_map_info = jf["MapAdditionalInfo"];

        m_enemyStarts = jf["MapAdditionalInfo"]["EnemyPos"];

        key_infos = jf["Tiles"];

        for (auto &&info : key_infos)
        {
            std::shared_ptr<Tile> tile = m_tile_set->find(info.type);
            m_layered_map[info.layer].emplace(info.coords, std::move(tile));
        }

        tiles.close();
    }

    void LayeredMap::set_tile_set(std::shared_ptr<TileSet> tile_set)
    {
        m_tile_set=tile_set;
    }

    void LayeredMap::draw()
    {
        sf::RenderWindow& l_wind = m_context.m_wind->GetRenderWindow();

        for (auto &&layer : m_layered_map)
        {
            for (auto &&tile : layer.second)
            {
                sf::Vector2i tile_size = tile.second->get_size();
                sf::Vector2f position = {
                    static_cast<float>(tile.first.x * tile_size.x), 
                    static_cast<float>(tile.first.y * tile_size.y)
                };
                tile.second->setPosition(position);
                l_wind.draw(*tile.second);
            }            
        }        
    }
} // namespace NewMap
