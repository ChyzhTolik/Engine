#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
    enum Sheet{ Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256, NumLairs = 4 };

    enum class TileType
    {
        None = -1,
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
        bool m_solid;
    };

    class Tile : public sf::Sprite
    {
    private:
    public:
        TileInfo m_tile_info;
        Tile() = default;
        Tile(const Tile&) = default;
        Tile(Tile&&) = default;
        Tile(TileInfo info);
        ~Tile();
        // TileType get_type() const;
        int get_width() const;
        int get_height() const;

        template<typename T>
        T get_type() const;

        template<typename T>
        void set_type(T type);

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
} // namespace Engine
