#include "TileSet.hpp"

#include <fstream>

namespace NewMap
{
    TileSet::TileSet(/* args */)
    {
    }
    
    TileSet::~TileSet()
    {
    }

    void TileSet::load_from_file(const std::string& file_name)
    {
        std::ifstream tiles(std::string(file_name));


    }
} // namespace NewMap
