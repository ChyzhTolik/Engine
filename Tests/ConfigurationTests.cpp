#include <gtest/gtest.h>

#include <Configuration/Configuration.hpp>

TEST(ConfigurationTest, TestInitTextures)
{
    sf::RenderWindow window(sf::VideoMode({300,200}), "SFML works!");

    Engine::Configuration::Initialize();
    auto texture = Engine::Configuration::textures.get(Engine::Configuration::Textures::Intro);

    EXPECT_EQ(texture.getSize().x, 400);
    EXPECT_EQ(texture.getSize().y, 150);
}

