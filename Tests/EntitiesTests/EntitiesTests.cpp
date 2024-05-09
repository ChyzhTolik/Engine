#include <gtest/gtest.h>

#include <Animations/Animation.hpp>
#include <Animations/AnimatedSprite.hpp>
#include <Configuration/Configuration.hpp>
#include <Animations/SpriteSheetTemplate.hpp>
#include <Animations/AnimationTypes.hpp>
#include <Animations/Anim_Directional.hpp>

// class AnimationTestsFixture : public ::testing::Test
// {
// protected:
// 	void SetUp()
// 	{
// 		Engine::Configuration::Initialize();
// 	}
// 	void TearDown()
// 	{
// 	}
// };

// TEST_F(AnimationTestsFixture, TestAnimation)
// {
//     std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>(Engine::Configuration::textures.get(Engine::Configuration::Textures::Knigth));
//     Engine::Animation animation(texture->getSize());

//     animation.add_frame(sf::IntRect({0,0},{32,32}));
//     EXPECT_EQ(animation.get_rect(0).width, 32);
// }