#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
    enum Sheet{ Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256 };

    enum class TileType
    {
        None = 0,
        Grass,
        Dirt,
        Stone,
        Brick,
        Brick_Red,
        Rock,
        Icy_Rock,
        Spikes,
        Ice,
    };

    struct TileInfo
    {
        TileType type;
        bool is_deadly;
        sf::Vector2f friction;
        sf::Vector2i coords;
        sf::Vector2i size;
    };

    class Tile : public sf::Sprite
    {
    private:
    public:
        TileInfo m_tile_info;
        bool m_warp;
        Tile() = default;
        Tile(const Tile&) = default;
        Tile(Tile&&) = default;
        Tile(TileInfo info);
        ~Tile();
        TileType get_type() const;
        int get_width() const;
        int get_height() const;
    };
} // namespace Engine
