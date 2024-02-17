#pragma once

#include <string>
#include <memory>

namespace Engine
{
    class TileSetInterface
    {
    public:
        virtual ~TileSetInterface(){};

        virtual void load_from_file(const std::string& file_name) = 0;
        virtual uint32_t count() const = 0;
    };
    
} // namespace Engine
