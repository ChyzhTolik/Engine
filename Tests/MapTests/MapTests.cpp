#include <gtest/gtest.h>

#include <Map/TileTemplate.hpp>
#include <Map/KnightTiles.hpp>
#include <Configuration/Configuration.hpp>

TEST(MapTests, TileTemplateTests)
{
    Engine::TileInfo<Engine::KnightTiles> temp_tile_info{Engine::KnightTiles::Brick, false,{0.2f,0.f},{32,0},{32,32}};
	Engine::TileTemplate<Engine::KnightTiles> temp_tile(temp_tile_info, Engine::Configuration::Textures::TilesEngine);

    EXPECT_EQ(temp_tile.get_tile_info(), temp_tile_info);

    EXPECT_EQ(temp_tile.get_size(), temp_tile_info.size);

    EXPECT_EQ(temp_tile.get_friction(), temp_tile_info.friction);

    EXPECT_EQ(temp_tile.get_type(), Engine::KnightTiles::Brick);

    temp_tile.set_type(Engine::KnightTiles::Brick_Red);
    EXPECT_EQ(temp_tile.get_type(), Engine::KnightTiles::Brick_Red);

    temp_tile.set_friction({0.3f,0.3f});
    EXPECT_EQ(temp_tile.get_friction(), sf::Vector2f(0.3f,0.3f));
}