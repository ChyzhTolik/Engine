#include "TileSet.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace NewMap
{
    TileSet::TileSet(/* args */)
    {
    }
    
    TileSet::~TileSet()
    {
    }

    void to_json(json& j, const TileInfo& p) 
    {
        j = json
        { 
            {"coords", {p.coords.x, p.coords.y}}, 
            {"size", {p.size.x,p.size.y}}, 
            {"friction", {p.friction.x, p.friction.y}},
            {"type", p.type},
            {"is_deadly", p.is_deadly}
        };
    }

    void from_json(const json& j, TileInfo& p) 
    {
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

    void to_json(json& j, const TileSetInfo& p)
    {
        j = json
        {
            {"tiles_file_id", p.texture_id},
            {"tiles", p.tiles}
        };
    }

    void from_json(const json& j, TileSetInfo& p)
    {
        j.at("tiles_file_id").get_to(p.texture_id);
        j.at("tiles").get_to(p.tiles);
    }

    void TileSet::load_from_file(const std::string& file_name)
    {
        std::fstream tiles{file_name};

        if (!tiles.good())
        { 
            std::cout << "! Failed loading " << file_name << "." << std::endl; return; 
        }

	    json jf = json::parse(tiles);
        TileSetInfo set_info;
        set_info = jf;

        for (auto &&info : set_info.tiles)
        {
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(info, set_info.texture_id);
            m_set.emplace(info.type, std::move(tile));
        }        

        tiles.close();

    }

    std::shared_ptr<Tile> TileSet::get_tile(uint32_t id) const
    {
        if (m_set.find(id) != m_set.end())
        {
            return m_set.at(id);
        }
        else
        {
            return nullptr;
        }
    }
} // namespace NewMap
