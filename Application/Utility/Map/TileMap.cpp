#include "TileMap.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "StateManager.hpp"

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

    const sf::Vector2u& TileMap::GetMapSize()const
    {
        return m_maxMapSize; 
    }

    float TileMap::GetGravity()const
    {
        return m_mapGravity;
    }

    unsigned int TileMap::GetTileSize()const
    { 
        return Sheet::Tile_Size; 
    }

    Tile& TileMap::GetTile(unsigned int l_x, unsigned int l_y)
    {
        auto itr = m_map.find({l_x,l_y});

	    return *(itr->second);
    }

    void TileMap::LoadNext()
    {
        
    }

    const sf::Vector2f& TileMap::GetPlayerStart() const
    {
        return m_playerStart;
    }

    void TileMap::Update(float l_dT)
    {
        if(m_loadNextMap)
        {
            PurgeMap();
            m_loadNextMap = false;
            if(m_nextMap != ""){
                load_from_file("media/Maps/"+m_nextMap);
            } else {
                // m_context. GetStateManager().SwitchTo(StateType::GameOver);
            }
            m_nextMap = "";
        }
        sf::FloatRect viewSpace = m_context.m_wind.GetViewSpace();
        m_background->setPosition({viewSpace.left, viewSpace.top});
    }

    void TileMap::PurgeMap()
    {

    }

} // namespace Engine
