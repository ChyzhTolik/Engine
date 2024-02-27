#include "MapLayerFactory.hpp"

#include "MapLayerTemplate.hpp"
#include "KnightTiles.hpp"
#include "IsoTiles.hpp"

namespace Engine
{
    MapLayerFactory::MapLayerFactory(Engine::SharedContext& context, const std::vector<MapTileSetInfo>& tile_set_infos, std::string_view m_json_path)
        : m_context(context), m_json_path(m_json_path)
    {
        load_tilesets(tile_set_infos);
    }

    void MapLayerFactory::set_context(const SharedContext& context)
    {
        m_context = context;
    }

    void MapLayerFactory::set_json_path(std::string_view path)
    {
        m_json_path = path;
    }

    std::shared_ptr<MapLayerInterface> MapLayerFactory::get(std::string layer_type)
    {
        std::shared_ptr<MapLayerInterface> result = nullptr;

        if (layer_type == "IsoTileSet")
        {
            result = std::make_shared<MapLayerTemplate<IsoTiles>>(m_context);
            std::dynamic_pointer_cast<Engine::MapLayerTemplate<Engine::IsoTiles>>(result)->
			    set_tile_set(std::dynamic_pointer_cast<Engine::TileSetTemplate<Engine::IsoTiles>>(m_tile_sets[layer_type]));
        }

        if (layer_type == "KnightTileSet")
        {
            result = std::make_shared<MapLayerTemplate<KnightTiles>>(m_context);
            std::dynamic_pointer_cast<Engine::MapLayerTemplate<Engine::KnightTiles>>(result)->
			    set_tile_set(std::dynamic_pointer_cast<Engine::TileSetTemplate<Engine::KnightTiles>>(m_tile_sets[layer_type]));
        }
        
        return result;
    }

    void MapLayerFactory::load_tilesets(const std::vector<MapTileSetInfo>& tile_set_infos)
    {
        for (auto &&tile_set_info : tile_set_infos)
        {
            auto tile_set = get_tile_set(tile_set_info.name);

            if (tile_set == nullptr)
            {
                std::cout<<"Couldn't create tile set with a name: " << tile_set_info.name<<std::endl;
            }
            else
            {
                tile_set->load_from_file(m_json_path + tile_set_info.file);
                m_tile_sets[tile_set_info.name] = tile_set;
            }
        }
    }

    std::shared_ptr<TileSetInterface> MapLayerFactory::get_tile_set(std::string tile_set_name)
    {
        if (tile_set_name == "IsoTileSet")
        {
            return std::make_shared<TileSetTemplate<IsoTiles>>();
        }

        if (tile_set_name == "KnightTileSet")
        {
            return std::make_shared<TileSetTemplate<KnightTiles>>();
        }
        
        return nullptr;
    }
} // namespace Engine
