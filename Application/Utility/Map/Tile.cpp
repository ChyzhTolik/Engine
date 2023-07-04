#include "Tile.hpp"
#include "Configuration.hpp"

namespace Engine
{
    Tile::Tile(TileInfo info) : sf::Sprite(Configuration::textures.get(Configuration::Textures::TilesEngine)), 
        m_tile_info{info}
    {
        setTextureRect({m_tile_info.coords, m_tile_info.size});
    }

    Tile::~Tile()
    {

    }
} // namespace Engine
