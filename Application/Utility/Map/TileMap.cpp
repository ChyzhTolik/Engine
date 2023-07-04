#include "TileMap.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Engine
{
    

    TileMap::TileMap(SharedContext& context) : m_context(context)
    {
        m_tile_set.load_from_file("media/tiles.json");
        load_from_file("media/map.json");
    }
    
    TileMap::~TileMap()
    {
    }

    void TileMap::draw()
    {
        sf::RenderWindow& l_wind = m_context.m_wind.GetRenderWindow();
        sf::FloatRect viewSpace = m_context.m_wind.GetViewSpace();

        for (auto &&tile : m_map)
        {
            sf::Sprite& sprite = m_tile_set.get_tile(tile.second->get_type());
            sprite.setPosition({static_cast<float>(tile.first.x * tile.second->get_width()),
                static_cast<float>(tile.first.y * tile.second->get_height())});
            l_wind.draw(sprite);
        }
    }

    void to_json(json& j, const MapInfo& p) {
        j = json{ {"type", p.type}, {"coords", {p.coords.x, p.coords.y}} };
    }

    void from_json(const json& j, MapInfo& p) {

        j.at("type").get_to(p.type);

        int coords[2];
        j.at("coords").get_to(coords);
        p.coords = sf::Vector2i(coords[0],coords[1]);
    }

    void TileMap::load_from_file(std::string_view file)
    {
        std::ifstream tiles;
        tiles.open(std::string(file));

        if (!tiles.is_open())
        { 
            std::cout << "! Failed loading keys.json." << std::endl; return; 
        }

	    json jf = json::parse(tiles);
        std::vector<MapInfo> key_infos;
        key_infos = jf;

        for (auto &&info : key_infos)
        {
            std::shared_ptr<Tile> tile = m_tile_set.find(info.type);
            m_map.emplace(info.coords, std::move(tile));
        }        

        tiles.close();
    }
} // namespace Engine
