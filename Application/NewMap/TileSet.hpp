#pragma once

#include "Tile.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

namespace NewMap
{
    struct TileSetInfo
    {
        uint32_t texture_id;
        std::vector<TileInfo> tiles;
    };

    class TileSet
    {
    public:
        TileSet();
        ~TileSet();
        void load_from_file(const std::string& file_name);
        std::shared_ptr<Tile> get_tile(uint32_t id) const;
        uint32_t count() const;
    private:
        std::unordered_map<uint32_t, std::shared_ptr<Tile>> m_set;
    };
} // namespace NewMap
