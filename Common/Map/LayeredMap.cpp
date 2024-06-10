#include "LayeredMap.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "MapLayerFactory.hpp"

using nlohmann::json;

namespace Engine
{
    LayeredMap::LayeredMap(Engine::SharedContext& context): m_context(context)
    {

    }
        
    LayeredMap::~LayeredMap()
    {

    }

    void to_json(json& j, const MapSize& p) {
        j = json{ {"width", p.width}, {"height", p.height} };
    }

    void from_json(const json& j, MapSize& p) {

        j.at("width").get_to(p.width);
        j.at("height").get_to(p.height);
    }

    void to_json(json& j, const EnemyPositionInfo& p) {
        j = json{ {"name", p.name}, {"coords", {p.coords.x, p.coords.y}} };
    }

    void from_json(const json& j, EnemyPositionInfo& p) {

        j.at("name").get_to(p.name);

        float coords[2];
        j.at("coords").get_to(coords);
        p.coords = sf::Vector2f(coords[0],coords[1]);
    }

    void to_json(json& j, const MapTileSetInfo& p) {
        j = json{ {"name", p.name}, {"file", p.file} };
    }

    void from_json(const json& j, MapTileSetInfo& p) {

        j.at("name").get_to(p.name);
        j.at("file").get_to(p.file);
    }

    void to_json(json& j, const MapLayerInfo& p) {
        j = json{ 
            {"TileSet", p.tile_set_name}, 
            {"file", p.file},
            {"Position", p.position},
            {"Solid", p.is_solid}
        };
    }

    void from_json(const json& j, MapLayerInfo& p) {

        j.at("TileSet").get_to(p.tile_set_name);
        j.at("file").get_to(p.file);
        j.at("Position").get_to(p.position);
        j.at("Solid").get_to(p.is_solid);
    }

    void to_json(json& j, const MapAdditionalInfo& p) {
        j = json
        {
            {"Warp", {p.warp.x, p.warp.y}},
            {"MapSize", p.m_maxMapSize}, 
            {"Gravity", p.m_mapGravity},
            {"PlayerStartPos", {p.m_playerStart.x, p.m_playerStart.y}},
            {"NextMap", p.next_map},
            {"Friction", {p.friction.x, p.friction.y}},
            {"EnemyPositions", p.enemy_positions},
            {"Layers",p.layers},
            {"TileSets",p.tile_sets},
            {"FolderPath",p.jsons_path},
            {"main_layer_position",p.main_layer_position},
        };
    }

    void from_json(const json& j, MapAdditionalInfo& p) {

        j.at("Gravity").get_to(p.m_mapGravity);
        j.at("NextMap").get_to(p.next_map);

        unsigned int coords_u[2];
        j.at("Warp").get_to(coords_u);
        p.warp = sf::Vector2u(coords_u[0],coords_u[1]);

        j.at("MapSize").get_to(p.m_maxMapSize);

        float coords_f[2];
        j.at("PlayerStartPos").get_to(coords_f);
        p.m_playerStart = sf::Vector2f(coords_f[0],coords_f[1]);

        j.at("Friction").get_to(coords_f);
        p.friction = sf::Vector2f(coords_f[0],coords_f[1]);

        j.at("EnemyPositions").get_to(p.enemy_positions);
        j.at("Layers").get_to(p.layers);
        j.at("TileSets").get_to(p.tile_sets);
        j.at("FolderPath").get_to(p.jsons_path);
        j.at("main_layer_position").get_to(p.main_layer_position);
    }

    void LayeredMap::load_from_file(const std::string& file_name)
    {
        std::fstream map_file{file_name};

        if (!map_file.good())
        { 
            std::cout << "! Failed loading " << file_name << "." << std::endl; return; 
        }

	    json jf = json::parse(map_file);
        m_map_info = jf;

        std::unique_ptr<MapLayerFactory> layer_factory = std::make_unique<MapLayerFactory>(m_context, m_map_info.tile_sets, m_map_info.jsons_path);

        for (auto &&layer_info : m_map_info.layers)
        {
            auto layer = layer_factory->get(layer_info.tile_set_name);

            if (layer == nullptr)
            {
                std::cout<<"Couldn't create layer with a tile_set type: " << layer_info.tile_set_name<<std::endl;
            }
            else
            {
                layer->load_from_file(m_map_info.jsons_path + layer_info.file);
            }

            layer->set_is_solid(layer_info.is_solid);

            m_layers[layer_info.position] = layer;
        }

        m_main_layer = m_layers.at(m_map_info.main_layer_position);
        m_default_friction = m_map_info.friction;
        m_warp_coords = m_map_info.warp;
    }

    void LayeredMap::draw()
    {   
        for (auto &&layer : m_layers)
        {
            layer.second->draw();
        }           
    }

    size_t LayeredMap::layers_count() const
    {
        return m_layers.size();
    }

    sf::Vector2u LayeredMap::get_map_size() const
    {
        return sf::Vector2u(m_map_info.m_maxMapSize.width, m_map_info.m_maxMapSize.height);
    }

    sf::Vector2u LayeredMap::get_tile_size() const
    {
        return m_main_layer->get_tile_size();
    }

    float LayeredMap::get_gravity() const
    {
        return m_map_info.m_mapGravity;
    }

    sf::Vector2f LayeredMap::get_default_friction() const
    {
        return m_default_friction;
    }

    std::shared_ptr<Tile> LayeredMap::get_tile(int32_t layer, const sf::Vector2i& coords) const
    {
        return m_layers.at(layer)->get_tile_at(coords);
    }

    sf::Vector2u LayeredMap::get_warp_coords() const
    {
        return m_warp_coords;
    }

    void LayeredMap::load_next_map()
    {

    }

    int LayeredMap::get_main_layer_index() const
    {
        return m_map_info.main_layer_position;
    }

    bool LayeredMap::is_solid(int32_t layer) const
    {
        return m_layers.at(layer)->is_solid();
    }
} // namespace Engine
