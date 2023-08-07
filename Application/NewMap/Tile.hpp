#pragma once

#include "Configuration.hpp"
#include <SFML/Graphics.hpp>

namespace NewMap
{
    struct TileInfo
    {
        uint32_t type;
        bool is_deadly;
        sf::Vector2f friction;
        sf::Vector2i coords;
        sf::Vector2i size;
    };

    class Tile : public sf::Sprite
    {
    public:
        Tile(const TileInfo& tile_info, u_int32_t texture_id);
        ~Tile();

        TileInfo get_tile_info() const;
    private:
        const sf::Texture& get_texture(uint32_t texture_id);
        TileInfo m_tile_info;
    };
    
    
    
} // namespace NewMap
