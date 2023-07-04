#include "TileSet.hpp"
#include "Tile.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using nlohmann::json;

namespace Engine
{
    void to_json(json& j, const TileInfo& p) {
        j = json
        { 
            {"coords", {p.coords.x, p.coords.y}}, 
            {"size", {p.size.x,p.size.y}}, 
            {"friction", {p.friction.x, p.friction.y}},
            {"type", p.type},
            {"is_deadly", p.is_deadly}
        };
    }

    void from_json(const json& j, TileInfo& p) {
        float float_array[2];
        j.at("friction").get_to(float_array);
        p.friction = sf::Vector2f(float_array[0],float_array[1]);

        int int_array[2];
        j.at("coords").get_to(int_array);
        p.coords = sf::Vector2i(int_array[0],int_array[1]);

        j.at("size").get_to(int_array);
        p.size = sf::Vector2i(int_array[0],int_array[1]);

        j.at("type").get_to(p.type);
        j.at("is_deadly").get_to(p.is_deadly);
    }

    void TileSet::load_from_file(std::string_view file_name)
    {
        std::ifstream tiles;
        tiles.open(std::string(file_name));

        if (!tiles.is_open())
        { 
            std::cout << "! Failed loading keys.json." << std::endl; return; 
        }

	    json jf = json::parse(tiles);
        std::vector<TileInfo> key_infos;
        key_infos = jf;

        for (auto &&info : key_infos)
        {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(info);
            m_set.emplace(TileType(info.type), std::move(tile));
        }        

        tiles.close();
    }

    sf::Sprite& TileSet::get_tile(TileType type) const
    {
        return *m_set.at(type);
    }

    std::shared_ptr<Tile> TileSet::find(TileType type) const
    {
        return m_set.find(type)->second;
    }
} // namespace Engine
