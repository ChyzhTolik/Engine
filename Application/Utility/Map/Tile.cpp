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

    // TileType Tile::get_type() const
    // {
    //     return m_tile_info.type;
    // }

    int Tile::get_width() const
    {
        return m_tile_info.size.x;
    }

    int Tile::get_height() const
    {
        return m_tile_info.size.y;
    }
} // namespace Engine
