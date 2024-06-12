#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

namespace Engine
{
    class MapLayerInterface
    {
    public:
        virtual ~MapLayerInterface(){}
        void virtual load_from_file(const std::string& file_name) = 0;
        void virtual draw() = 0;
        virtual sf::Vector2u get_tile_size() const = 0;
        virtual std::shared_ptr<Tile> get_tile_at(const sf::Vector2i& coords) = 0;
        virtual bool is_solid() const = 0;
        virtual void set_is_solid(bool solid) = 0;
    };    
} // namespace Engine
