#pragma once

#include "TileTemplate.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

namespace Engine
{
    using nlohmann::json;

    template<typename TyleType = uint32_t>
    struct TileSetInfo
    {
        Configuration::Textures texture_id;
        std::vector<TileInfo<TyleType>> tiles;
    };

    template<typename TyleType>
    class TileSetTemplate
    {
    public:
        TileSetTemplate(/* args */);
        ~TileSetTemplate();

        void load_from_file(const std::string& file_name);
        std::shared_ptr<TileTemplate<TyleType>> get_tile(TyleType id) const;
        uint32_t count() const;
        void test_json();
    private:
        std::unordered_map<uint32_t, std::shared_ptr<TileTemplate<TyleType>>> m_set;
    };
    
    template<typename TyleType>
    TileSetTemplate<TyleType>::TileSetTemplate(/* args */)
    {
    }
    
    template<typename TyleType>
    TileSetTemplate<TyleType>::~TileSetTemplate()
    {
    }

    template<typename TyleType>
    uint32_t TileSetTemplate<TyleType>::count() const
    {
        return m_set.size();
    }

    template<typename TyleType>
    void to_json(json& j, const TileInfo<TyleType>& p) 
    {
        j = json
        { 
            {"coords", {p.coords.x, p.coords.y}}, 
            {"size", {p.size.x,p.size.y}}, 
            {"friction", {p.friction.x, p.friction.y}},
            {"type", static_cast<uint32_t>(p.type)},
            {"is_deadly", p.is_deadly}
        };
    }

    template<typename TyleType>
    void from_json(const json& j, TileInfo<TyleType>& p) 
    {
        float float_array[2];
        j.at("friction").get_to(float_array);
        p.friction = sf::Vector2f(float_array[0],float_array[1]);

        int int_array[2];
        j.at("coords").get_to(int_array);
        p.coords = sf::Vector2i(int_array[0],int_array[1]);

        j.at("size").get_to(int_array);
        p.size = sf::Vector2i(int_array[0],int_array[1]);

        uint32_t tile_id;
        j.at("type").get_to(tile_id);
        p.type = TyleType(tile_id);

        j.at("is_deadly").get_to(p.is_deadly);
    }

    template<typename TyleType>
    void to_json(json& j, const TileSetInfo<TyleType>& p)
    {
        j = json
        {
            {"tiles_file_id", p.texture_id},
            {"tiles", p.tiles}
        };
    }

    template<typename TyleType>
    void from_json(const json& j, TileSetInfo<TyleType>& p)
    {
        std::vector<uint32_t> tile_ids;

        j.at("tiles_file_id").get_to(p.texture_id);
        j.at("tiles").get_to(p.tiles);        
    }

    template<typename TyleType>
    void TileSetTemplate<TyleType>::load_from_file(const std::string& file_name)
    {
        std::fstream tiles{file_name};

        if (!tiles.good())
        { 
            std::cout << "! Failed loading " << file_name << "." << std::endl; return; 
        }

	    json jf = json::parse(tiles);
        TileSetInfo<TyleType> set_info;
        set_info = jf;

        for (auto &&info : set_info.tiles)
        {
            std::shared_ptr<TileTemplate<TyleType>> tile = std::make_shared<TileTemplate<TyleType>>(info, set_info.texture_id);
            // m_set.emplace(info.type, std::move(tile));
        }
    }

    template<typename TyleType>
    std::shared_ptr<TileTemplate<TyleType>> TileSetTemplate<TyleType>::get_tile(TyleType id) const
    {
        return nullptr;
    }

    template<typename TyleType>
    void TileSetTemplate<TyleType>::test_json()
    {
        
    }
    
} // namespace Engine
