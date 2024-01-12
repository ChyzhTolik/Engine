#pragma once

#include "Configuration/Configuration.hpp"
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
        Tile(const TileInfo& tile_info, uint32_t texture_id);
        ~Tile();

        TileInfo get_tile_info() const;

        template<typename T>
        T get_type() const;

        template<typename T>
        void set_type(T type);

        sf::Vector2f get_friction() const;
        void set_friction(const sf::Vector2f& friction);
        sf::Vector2i get_size() const;
        bool is_deadly() const;
    private:
        const sf::Texture& get_texture(uint32_t texture_id);
        TileInfo m_tile_info;
    };
    
    template<typename T>
    T Tile::get_type() const
    {
        return T(m_tile_info.type);
    }

    template<typename T>
    void Tile::set_type(T type)
    {
        m_tile_info.type = static_cast<uint32_t>(type);
    }
    
} // namespace NewMap
