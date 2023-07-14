#include "TileMap.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "StateManager.hpp"
#include "Configuration.hpp"

using nlohmann::json;

namespace Engine
{
    

    TileMap::TileMap(SharedContext& context) : m_context(context), m_loadNextMap(false),
        m_background(std::make_shared<sf::Sprite>(Configuration::textures.get(Configuration::Textures::Background)))
    {
        m_tile_set.load_from_file("media/Json/tiles.json");
        load_from_file("media/Json/map.json");
    }
    
    TileMap::~TileMap()
    {
    }

    void TileMap::draw()
    {
        sf::RenderWindow& l_wind = m_context.m_wind->GetRenderWindow();
        sf::FloatRect viewSpace = m_context.m_wind->GetViewSpace();

        for (auto &&tile : m_map)
        {
            sf::Sprite& sprite = m_tile_set.get_tile(tile.second->get_type());
            sprite.setPosition({static_cast<float>(tile.first.x * tile.second->get_width()),
                static_cast<float>(tile.first.y * tile.second->get_height())});
            l_wind.draw(sprite);
        }
    }

    void to_json(json& j, const MapTileInfo& p) {
        j = json{ {"type", p.type}, {"coords", {p.coords.x, p.coords.y}} };
    }

    void from_json(const json& j, MapTileInfo& p) {

        j.at("type").get_to(p.type);

        int coords[2];
        j.at("coords").get_to(coords);
        p.coords = sf::Vector2i(coords[0],coords[1]);
    }

    void to_json(json& j, const MapAdditionalInfo& p) {
        j = json{ 
            {"MapSize", {p.m_maxMapSize.x, p.m_maxMapSize.y}}, 
            {"Gravity", p.m_mapGravity},
            {"PlayerStartPos", {p.m_playerStart.x, p.m_playerStart.y}},
            {"Friction", {p.friction.x, p.friction.y}}
        };
    }

    void from_json(const json& j, MapAdditionalInfo& p) {

        j.at("Gravity").get_to(p.m_mapGravity);

        unsigned int coords_u[2];
        j.at("MapSize").get_to(coords_u);
        p.m_maxMapSize = sf::Vector2u(coords_u[0],coords_u[1]);

        float coords_f[2];
        j.at("PlayerStartPos").get_to(coords_f);
        p.m_playerStart = sf::Vector2f(coords_f[0],coords_f[1]);

        j.at("Friction").get_to(coords_f);
        p.friction = sf::Vector2f(coords_f[0],coords_f[1]);
    }

    void TileMap::load_from_file(std::string_view file)
    {
        std::ifstream tiles;
        tiles.open(std::string(file));

        if (!tiles.is_open())
        { 
            std::cout << "! Failed loading "<<file<<"." << std::endl; return; 
        }

	    json jf = json::parse(tiles);
        std::vector<MapTileInfo> key_infos;
        MapAdditionalInfo add_info;
        add_info = jf["MapAdditionalInfo"];

        m_maxMapSize = add_info.m_maxMapSize;
        m_playerStart = add_info.m_playerStart;
        m_mapGravity = add_info.m_mapGravity;

        key_infos = jf["Tiles"];

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

    std::shared_ptr<Tile> TileMap::GetTile(unsigned int l_x, unsigned int l_y)
    {
        auto itr = m_map.find({l_x,l_y});

        if (itr==m_map.end())
        {
            return nullptr;
        }
        
	    return itr->second;
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
        sf::FloatRect viewSpace = m_context.m_wind->GetViewSpace();
        m_background->setPosition({viewSpace.left, viewSpace.top});
    }

    void TileMap::PurgeMap()
    {

    }

} // namespace Engine
