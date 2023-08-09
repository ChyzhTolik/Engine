#pragma once

#include "Tile.hpp"
#include <unordered_map>

namespace NewMap
{
    class TileSet
    {
    public:
        TileSet(/* args */);
        ~TileSet();
        void load_from_file(const std::string& file_name);
    private:
        std::unordered_map<int, Tile> m_set;
    };    
} // namespace NewMap
