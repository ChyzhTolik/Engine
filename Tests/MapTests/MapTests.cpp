#include <gtest/gtest.h>

#include <Map/TileTemplate.hpp>
#include <Map/KnightTiles.hpp>
#include <Map/TileSetTemplate.hpp>
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

TEST(MapTest, TileSetTemplateTests)
{
    Engine::TileInfo<Engine::KnightTiles> temp_tile_info{Engine::KnightTiles::Brick, false,{0.2f,0.f},{32,0},{32,32}};

    json j;
    j = temp_tile_info;

    Engine::TileInfo<Engine::KnightTiles> new_tile_info = j;

    EXPECT_EQ(new_tile_info, temp_tile_info);

    auto type = new_tile_info.type;
    Engine::TileTemplate<Engine::KnightTiles> temp_tile(temp_tile_info, Engine::Configuration::Textures::TilesEngine);

    Engine::TileSetInfo<Engine::KnightTiles> tile_set_info;
    tile_set_info.texture_id=Engine::Configuration::Textures::TilesEngine;
    tile_set_info.tiles.push_back(temp_tile_info);
    tile_set_info.tiles.push_back(new_tile_info);

    json jey;
    jey = tile_set_info;

    Engine::TileSetInfo<Engine::KnightTiles> new_tile_set_info = jey;
    EXPECT_EQ(tile_set_info.texture_id, new_tile_set_info.texture_id);
    EXPECT_EQ(tile_set_info.tiles, new_tile_set_info.tiles);
    new_tile_set_info.tiles.back().is_deadly = !new_tile_set_info.tiles.back().is_deadly;
    EXPECT_NE(tile_set_info.tiles, new_tile_set_info.tiles);

    Engine::TileSetTemplate<Engine::KnightTiles> tile_set;
    tile_set.load_from_file("media/Json/IsometricTiles.json");
    EXPECT_EQ(tile_set.count(), 5);

    const auto tile = tile_set.get_tile(Engine::KnightTiles::Brick);
    EXPECT_EQ(tile->get_size(), sf::Vector2i(32,32));
    EXPECT_EQ(tile->get_friction(), sf::Vector2f(0.9f,0.f));
    EXPECT_EQ(tile->getTextureRect().getPosition(), sf::Vector2i(96,0));

    Engine::TileSetTemplate<std::string> tile_set_string;
    tile_set_string.load_from_file("media/Json/IsometricTiles_string.json");
    EXPECT_EQ(tile_set.count(), 5);

    const auto tile_string = tile_set_string.get_tile("GrassJungle");
    EXPECT_EQ(tile_string->get_size(), sf::Vector2i(32,32));
    EXPECT_EQ(tile_string->get_friction(), sf::Vector2f(0.9f,0.f));
    EXPECT_EQ(tile_string->getTextureRect().getPosition(), sf::Vector2i(64,0));
}