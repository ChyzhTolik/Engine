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
        PurgeMap();
    }

    void TileMap::draw()
    {
        sf::RenderWindow& l_wind = m_context.m_wind->GetRenderWindow();

        for (auto &&tile : m_map)
        {
            sf::Sprite& sprite = m_tile_set.get_tile(tile.second->get_type());
            sprite.setPosition({
                static_cast<float>(tile.first.x * tile.second->get_width()),
                static_cast<float>(tile.first.y * tile.second->get_height())
            });
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

    void to_json(json& j, const EnemyMapInfo& p) {
        j = json{ {"name", p.name}, {"coords", {p.coords.x, p.coords.y}} };
    }

    void from_json(const json& j, EnemyMapInfo& p) {

        j.at("name").get_to(p.name);

        float coords[2];
        j.at("coords").get_to(coords);
        p.coords = sf::Vector2f(coords[0],coords[1]);
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

        m_additional_info = jf["MapAdditionalInfo"];

        m_defaultTile.friction = m_additional_info.friction;
        m_enemyStarts = jf["MapAdditionalInfo"]["EnemyPos"];

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
        return m_additional_info.m_maxMapSize; 
    }

    float TileMap::GetGravity()const
    {
        return m_additional_info.m_mapGravity;
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
        m_loadNextMap = true;
    }

    const sf::Vector2f& TileMap::GetPlayerStart() const
    {
        return m_additional_info.m_playerStart;
    }

    void TileMap::Update(float l_dT)
    {
        if(m_loadNextMap)
        {
            PurgeMap();
            m_loadNextMap = false;
            if(m_additional_info.next_map != "")
            {
                load_from_file("media/Json/"+ m_additional_info.next_map );
            } 
            else 
            {
                // m_context. GetStateManager().SwitchTo(StateType::GameOver);
            }
            m_additional_info.next_map  = "";
        }
        sf::FloatRect viewSpace = m_context.m_wind->GetViewSpace();
        m_background->setPosition({viewSpace.left, viewSpace.top});
    }

    void TileMap::PurgeMap()
    {
        m_map.clear();
        m_context.m_entityManager->Purge();
    }

    sf::Vector2u TileMap::get_warp_pos() const
    {
        return m_additional_info.warp;
    }

    int TileMap::get_player_id() const
    {
        return m_player_id;
    }

    void TileMap::draw_layer(int layer)
    {
        auto itr = m_map_layers.find(layer);

        if (itr == m_map_layers.end())
        {
            return;
        }

        sf::RenderWindow& l_wind = m_context.m_wind->GetRenderWindow();

        for (auto &&tile : m_map_layers.at(layer))
        {
            sf::Sprite& sprite = m_tile_set.get_tile(tile.second->get_type());
            sprite.setPosition({
                static_cast<float>(tile.first.x * tile.second->get_width()),
                static_cast<float>(tile.first.y * tile.second->get_height())
            });

            l_wind.draw(sprite);
        }
    }

    std::shared_ptr<Tile> TileMap::get_tile_on_layer(uint32_t x, uint32_t y, int layer)
    {
        if(x < 0 || y < 0 || x >= m_additional_info.m_maxMapSize.x || y >= m_additional_info.m_maxMapSize.y 
            || layer < 0 ||  layer >= Sheet::NumLairs)
        {
            return nullptr;
        }

        auto itr = m_map_layers.find(layer);

        if (itr == m_map_layers.end())
        {
            return nullptr;
        }
        
        auto map_itr = m_map_layers.at(layer).find(sf::Vector2u(x,y));

        if (map_itr == m_map_layers.at(layer).end())
        {
            return nullptr;
        }
        
        return map_itr->second;
    }
} // namespace Engine
