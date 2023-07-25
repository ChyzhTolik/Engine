#pragma once

#include "Tile.hpp"
#include <unordered_map>
#include <memory>
#include <string_view>

namespace Engine
{
    class TileSet
    {
    private:
        std::unordered_map<TileType, std::shared_ptr<Tile>> m_set;
    public:
        TileSet() = default;
        ~TileSet(){};
        void clear();
        void load_from_file(std::string_view file_name);
        sf::Sprite& get_tile(TileType type) const;
        std::shared_ptr<Tile> find(TileType type) const;
    };
} // namespace Engine
