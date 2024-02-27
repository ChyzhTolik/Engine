#pragma once

#include <memory>
#include "MapLayerTemplate.hpp"
#include "TileSetInterface.hpp"
#include "MapStructs.hpp"

namespace Engine
{
    class MapLayerFactory
    {
    public:
        MapLayerFactory(Engine::SharedContext& context, const std::vector<MapTileSetInfo>& tile_set_infos, std::string_view m_json_path);
        virtual ~MapLayerFactory(){}

        void set_context(const SharedContext& context);
        void set_json_path(std::string_view path);
        std::shared_ptr<MapLayerInterface> get(std::string layer_type);
    private:
        std::shared_ptr<TileSetInterface> get_tile_set(std::string tile_set_name);
        void load_tilesets(const std::vector<MapTileSetInfo>& tile_set_infos);

        std::unordered_map<std::string, std::shared_ptr<TileSetInterface>> m_tile_sets;
        std::string m_json_path;
        SharedContext& m_context;
    };
    
} // namespace Engine
