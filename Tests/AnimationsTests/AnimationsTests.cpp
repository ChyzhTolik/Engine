#include <gtest/gtest.h>

#include <Animations/Animation.hpp>
#include <Animations/AnimatedSprite.hpp>
#include <Configuration/Configuration.hpp>

class AnimationTestsFixture : public ::testing::Test
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

TEST_F(AnimationTestsFixture, TestAnimation)
{
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>(Engine::Configuration::textures.get(Engine::Configuration::Textures::Knigth));
    Engine::Animation animation(texture->getSize());

    animation.add_frame(sf::IntRect({0,0},{32,32}));
    EXPECT_EQ(animation.get_rect(0).width, 32);
}

TEST_F(AnimationTestsFixture, TestAnimatedSprite)
{
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>(Engine::Configuration::textures.get(Engine::Configuration::Textures::Knigth));
    std::shared_ptr<Engine::Animation> animation = std::make_shared<Engine::Animation>(texture->getSize());

    for (int i = 0; i < 8; i++)
    {
        animation->add_frame(sf::IntRect({0,0},{32*(i+1),32}));
    }

    Engine::AnimatedSprite animated_sprite(*texture, animation, Engine::AnimatedSprite::Status::Playing);
    animated_sprite.set_animation(animation);
    
    EXPECT_EQ(animation->get_rect(0).width, 32);
}