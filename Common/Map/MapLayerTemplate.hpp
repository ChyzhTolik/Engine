#pragma once

#include "TileSetTemplate.hpp"
#include "CommonHeaders/SharedContext.hpp"
#include "Vector2i_hash.hpp"
#include <fstream>

namespace Engine
{
    template<typename TileType>
    struct LayerTileInfo
    {
        TileType type;
        sf::Vector2i coords;
    };

    template<typename TileType>
    class MapLayerTemplate
    {
    public:
        MapLayerTemplate(SharedContext& context);
        ~MapLayerTemplate();
        void load_from_file(const std::string& file_name);
        void set_tile_set(std::shared_ptr<TileSetTemplate<TileType>> tile_set);
        void draw();
    private:
        Engine::SharedContext&  m_context;
        std::shared_ptr<TileSetTemplate<TileType>> m_tile_set;
        std::unordered_map<sf::Vector2i,std::shared_ptr<TileTemplate<TileType>>,Common::Vector2i_hash> m_map;
    };
    
    template<typename TileType>
    MapLayerTemplate<TileType>::MapLayerTemplate(SharedContext& context) : m_context(context)
    {
    }
    
    template<typename TileType>
    MapLayerTemplate<TileType>::~MapLayerTemplate()
    {
    }

    template<typename TileType>
    void MapLayerTemplate<TileType>::set_tile_set(std::shared_ptr<TileSetTemplate<TileType>> tile_set)
    {
        m_tile_set = tile_set;
    }

    template<typename TileType>
    void to_json(json& j, const LayerTileInfo<TileType>& p) 
    {
        j = json
        {
            {"coords", {p.coords.x, p.coords.y}},
            {"type", p.type}
        };
    }

    template<typename TileType>
    void from_json(const json& j, LayerTileInfo<TileType>& p) 
    {
        int int_array[2];
        j.at("coords").get_to(int_array);
        p.coords = sf::Vector2i(int_array[0],int_array[1]);

        j.at("type").get_to(p.type );
    }

    template<typename TileType>
    void MapLayerTemplate<TileType>::load_from_file(const std::string& file_name)
    {
        std::fstream tiles_file{file_name};

        if (!tiles_file.good())
        { 
            std::cout << "! Failed loading " << file_name << "." << std::endl; return; 
        }

	    json jf = json::parse(tiles_file);
        std::vector<LayerTileInfo<TileType>> tiles = jf;
        
        for (auto &&info : tiles)
        {
            std::shared_ptr<TileTemplate<TileType>> tile = m_tile_set->get_tile(info.type);
            m_map.emplace(info.coords, std::move(tile));
        }
    }

    template<typename TileType>
    void MapLayerTemplate<TileType>::draw()
    {
        sf::RenderWindow& l_wind = m_context.m_wind->GetRenderWindow();

        for (auto &&tile : m_map)
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
} // namespace Engine
