#pragma once

#include <string>
#include <memory>
#include <vector>
#include <typeinfo>
#include "TileSetInterface.hpp"
#include "TileSetTemplate.hpp"
#include "KnightTiles.hpp"
#include "IsoTiles.hpp"

namespace Engine
{
    class TileSetFactory
    {
    public:
        TileSetFactory(/* args */);
        virtual ~TileSetFactory();

        template<typename TileType>
        std::shared_ptr<TileSetInterface> get();
    private:
        std::vector<std::shared_ptr<TileSetInterface>> m_tilesets;
    };
    
    TileSetFactory::TileSetFactory(/* args */)
    {
    }
    
    TileSetFactory::~TileSetFactory()
    {
    }

    template<typename TileType>
    std::shared_ptr<TileSetInterface> TileSetFactory::get()
    {
        return std::make_shared<TileSetTemplate<TileType>>();
    }
    
} // namespace Engine
