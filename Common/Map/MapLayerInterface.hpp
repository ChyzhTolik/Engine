#pragma once

#include <string>
#include <memory>

namespace Engine
{
    class MapLayerInterface
    {
    public:
        virtual ~MapLayerInterface(){}
        void virtual load_from_file(const std::string& file_name) = 0;
        // void virtual set_tile_set(std::shared_ptr<TileSetTemplate<TileType>> tile_set) = 0;
        void virtual draw() = 0;
        // uint32_t count() const;
    };    
} // namespace Engine
