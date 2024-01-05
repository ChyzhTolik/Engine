#include <gtest/gtest.h>

#include <Configuration/Configuration.hpp>

TEST(ExampleTest, Test2)
{
    Engine::Configuration::Initialize();
    auto texture = Engine::Configuration::textures.get(Engine::Configuration::Textures::Biomenace);

    EXPECT_EQ(texture.getSize().x, 20);
}