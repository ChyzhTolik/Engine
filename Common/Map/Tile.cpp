#include "Tile.hpp"

namespace NewMap
{
    Tile::Tile(const TileInfo& tile_info, uint32_t texture_id) : sf::Sprite(get_texture(texture_id)), m_tile_info(tile_info)
    {
        setTextureRect({m_tile_info.coords, m_tile_info.size});
    }
    
    Tile::~Tile()
    {
    }

    TileInfo Tile::get_tile_info() const
    {
        return m_tile_info;
    }

    const sf::Texture& Tile::get_texture(uint32_t texture_id)
    {
        return Engine::Configuration::textures.get(Engine::Configuration::Textures(texture_id));
    }

    sf::Vector2f Tile::get_friction() const
    {
        return m_tile_info.friction;
    }

    sf::Vector2i Tile::get_size() const
    {
        return m_tile_info.size;
    }

    bool Tile::is_deadly() const
    {
        return m_tile_info.is_deadly;
    }

    void Tile::set_friction(const sf::Vector2f& friction)
    {
        m_tile_info.friction = friction;
    }
} // namespace NewMap
