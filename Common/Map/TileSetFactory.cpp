#include "TileSetFactory.hpp"

#include "TileSetTemplate.hpp"
#include "KnightTiles.hpp"
#include "IsoTiles.hpp"

namespace Engine
{
    std::shared_ptr<TileSetInterface> TileSetFactory::get(std::string tile_set_name)
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
