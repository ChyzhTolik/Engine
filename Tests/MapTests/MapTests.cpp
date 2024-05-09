#include <gtest/gtest.h>

#include <Map/TileTemplate.hpp>
#include <Map/KnightTiles.hpp>
#include <Map/TileSetTemplate.hpp>
#include <Map/MapLayerTemplate.hpp>
#include <Map/LayeredMap.hpp>
#include <Configuration/Configuration.hpp>
#include <CommonHeaders/SharedContext.hpp>

class MapTestsFixture : public ::testing::Test
{
protected:
	void SetUp()
	{
		Engine::Configuration::Initialize();
	}
	void TearDown()
	{
	}
};

TEST(MapTests, TileTemplateTests)
{
    Engine::TileInfo<Engine::KnightTiles> temp_tile_info{Engine::KnightTiles::Brick, false,{0.2f,0.f},{32,0},{32,32}};
	Engine::TileTemplate<Engine::KnightTiles> temp_tile(temp_tile_info, Engine::Configuration::Textures::TilesEngine);

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
    new_tile_info.size = temp_tile_info.size;

    EXPECT_EQ(new_tile_info.coords, temp_tile_info.coords);
    EXPECT_EQ(new_tile_info.friction, temp_tile_info.friction);
    EXPECT_EQ(new_tile_info.is_deadly, temp_tile_info.is_deadly);
    EXPECT_EQ(new_tile_info.type, temp_tile_info.type);

    auto type = new_tile_info.type;
    Engine::TileTemplate<Engine::KnightTiles> temp_tile(temp_tile_info, Engine::Configuration::Textures::TilesEngine);

    Engine::TileSetInfo<Engine::KnightTiles> tile_set_info;
    tile_set_info.tile_size = sf::Vector2i(32,32);
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
    tile_set.load_from_file("media/map/IsometricTiles.json");
    EXPECT_EQ(tile_set.count(), 5);

    const auto tile = tile_set.get_tile(Engine::KnightTiles::Brick);
    EXPECT_EQ(tile->get_size(), sf::Vector2i(32,32));
    EXPECT_EQ(tile->get_friction(), sf::Vector2f(0.9f,0.f));
    EXPECT_EQ(tile->getTextureRect().getPosition(), sf::Vector2i(96,0));

    Engine::TileSetTemplate<std::string> tile_set_string;
    tile_set_string.load_from_file("media/map/IsometricTiles_string.json");
    EXPECT_EQ(tile_set.count(), 5);

    const auto tile_string = tile_set_string.get_tile("GrassJungle");
    EXPECT_EQ(tile_string->get_size(), sf::Vector2i(32,32));
    EXPECT_EQ(tile_string->get_friction(), sf::Vector2f(0.9f,0.f));
    EXPECT_EQ(tile_string->getTextureRect().getPosition(), sf::Vector2i(64,0));
}

TEST_F(MapTestsFixture, MapLayerTemplateTests)
{
    std::shared_ptr<Engine::TileSetTemplate<Engine::KnightTiles>> tile_set = std::make_shared<Engine::TileSetTemplate<Engine::KnightTiles>>();
	tile_set->load_from_file("media/map/IsometricTiles.json");

    Engine::SharedContext context;

    Engine::MapLayerTemplate<Engine::KnightTiles> layer(context);
    layer.set_tile_set(tile_set);
    layer.load_from_file("media/map/map_layer1.json");

    EXPECT_EQ(layer.count(), 12);

    auto tile = layer.get_tile_at({0,2});
    EXPECT_EQ(tile->get_friction(), sf::Vector2f(0.9f,0.f));
    EXPECT_EQ(tile->get_size(), sf::Vector2i(32,32));
    EXPECT_EQ(tile->is_deadly(), false);

    // {
    //     "coords" : [32,0],
    //     "size" : [32, 32],
    //     "friction": [0.9, 0],
    //     "type": 1,
    //     "is_deadly": false
    // },
}

TEST_F(MapTestsFixture, LayeredMapTests)
{
    Engine::SharedContext context;

    std::unique_ptr<Engine::LayeredMap> map = std::make_unique<Engine::LayeredMap>(context);

    map->load_from_file("media/map/GameMap.json");

    EXPECT_EQ(map->layers_count(), 2);
}