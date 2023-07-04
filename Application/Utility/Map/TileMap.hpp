#pragma once
#include "TileSet.hpp"
#include <string_view>
#include "../SharedContext.hpp"

namespace Engine
{
    struct MapInfo
    {
        TileType type;
        sf::Vector2i coords;
    };

    struct Vector2i_hash 
    {
        size_t operator()(const sf::Vector2i& p) const
        {
            auto hash1 = std::hash<int>{}(p.x);
            auto hash2 = std::hash<int>{}(p.y);
    
            if (hash1 != hash2) {
                return hash1 ^ hash2;             
            }
            
            // If hash1 == hash2, their XOR is zero.
            return hash1;
        }
    };

    class TileMap
    {
    private:
        TileSet m_tile_set;
        SharedContext&  m_context;
        std::unordered_map<sf::Vector2i,std::shared_ptr<Tile>,Vector2i_hash> m_map;
    public:
        void load_from_file(std::string_view file);
        void draw();
        TileMap(SharedContext& context);
        ~TileMap();
    };
} // namespace Engine
