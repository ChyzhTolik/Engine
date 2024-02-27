#pragma once

#include <string>
#include <memory>
#include <vector>
#include "TileSetInterface.hpp"

namespace Engine
{
    class TileSetFactory
    {
    public:
        static std::shared_ptr<TileSetInterface> get(std::string tile_set_name);
    private:
        std::vector<std::shared_ptr<TileSetInterface>> m_tilesets;
    };
} // namespace Engine
