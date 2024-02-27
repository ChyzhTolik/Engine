#pragma once

#include "TileTemplate.hpp"
#include "TileSetInterface.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <optional>
#include <iostream>

using nlohmann::json;
namespace Engine
{
    template<typename TileType = uint32_t>
    struct TileSetInfo
    {
        Configuration::Textures texture_id;
        std::vector<TileInfo<TileType>> tiles;
    };

    template<typename TileType>
    class TileSetTemplate : public TileSetInterface
    {
    public:
        TileSetTemplate(/* args */);
        ~TileSetTemplate();

        virtual void load_from_file(const std::string& file_name) override;
        std::shared_ptr<TileTemplate<TileType>> get_tile(TileType id) const;
        virtual uint32_t count() const override;
    private:
        std::unordered_map<TileType, std::shared_ptr<TileTemplate<TileType>>> m_set;
    };
    
    template<typename TileType>
    TileSetTemplate<TileType>::TileSetTemplate(/* args */)
    {
    }
    
    template<typename TileType>
    TileSetTemplate<TileType>::~TileSetTemplate()
    {
    }

    template<typename TileType>
    uint32_t TileSetTemplate<TileType>::count() const
    {
        return m_set.size();
    }

    template<typename TileType>
    void to_json(json& j, const TileInfo<TileType>& p) 
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

    template<typename TileType>
    void from_json(const json& j, TileInfo<TileType>& p) 
    {
        float float_array[2];
        j.at("friction").get_to(float_array);
        p.friction = sf::Vector2f(float_array[0],float_array[1]);

        int int_array[2];
        j.at("coords").get_to(int_array);
        p.coords = sf::Vector2i(int_array[0],int_array[1]);

        j.at("size").get_to(int_array);
        p.size = sf::Vector2i(int_array[0],int_array[1]);

        j.at("type").get_to(p.type );

        j.at("is_deadly").get_to(p.is_deadly);
    }

    template<typename TileType>
    void to_json(json& j, const TileSetInfo<TileType>& p)
    {
        j = json
        {
            {"tiles_file_id", p.texture_id},
            {"tiles", p.tiles}
        };
    }

    template<typename TileType>
    void from_json(const json& j, TileSetInfo<TileType>& p)
    {
        std::vector<uint32_t> tile_ids;

        j.at("tiles_file_id").get_to(p.texture_id);
        j.at("tiles").get_to(p.tiles);        
    }

    template<typename TileType>
    void TileSetTemplate<TileType>::load_from_file(const std::string& file_name)
    {
        std::fstream tiles{file_name};

        if (!tiles.good())
        { 
            std::cout << "! Failed loading " << file_name << "." << std::endl; return; 
        }

	    json jf = json::parse(tiles);
        TileSetInfo<TileType> set_info;
        set_info = jf;
        m_set.clear();

        for (auto &&info : set_info.tiles)
        {
            std::shared_ptr<TileTemplate<TileType>> tile = std::make_shared<TileTemplate<TileType>>(info, set_info.texture_id);
            m_set.emplace(info.type, std::move(tile));
        }
    }

    template<typename TileType>
    std::shared_ptr<TileTemplate<TileType>> TileSetTemplate<TileType>::get_tile(TileType id) const
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
} // namespace Engine
