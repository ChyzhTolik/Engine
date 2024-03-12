#include <gtest/gtest.h>

#include <Animations/Animation.hpp>
#include <Animations/AnimatedSprite.hpp>
#include <Configuration/Configuration.hpp>
#include <Animations/SpriteSheetTemplate.hpp>
#include <Animations/AnimationTypes.hpp>
#include <Animations/Anim_Directional.hpp>

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

TEST_F(AnimationTestsFixture, TestSpritesheet)
{
    std::shared_ptr<Engine::SpriteSheetTemplate<Engine::KnightAnimations>> sprite_sheet = 
        std::make_shared<Engine::SpriteSheetTemplate<Engine::KnightAnimations>>();

    sprite_sheet->LoadSheet<Engine::Anim_Directional>("media/Animations/Knight_Animations.json", Engine::Configuration::Textures::Knigth);
    sprite_sheet->SetAnimation(Engine::KnightAnimations::Idle);
    sprite_sheet->GetCurrentAnim()->Play();
    sprite_sheet->GetCurrentAnim()->SetLooping(true);
    auto current_animation = sprite_sheet->GetCurrentAnim();
    EXPECT_EQ(current_animation->is_playing(), true);
    EXPECT_EQ(current_animation->rects_count(), 8);

    sprite_sheet->SetAnimation(Engine::KnightAnimations::Walk);
    sprite_sheet->GetCurrentAnim()->Stop();
    current_animation = sprite_sheet->GetCurrentAnim();
    EXPECT_EQ(current_animation->is_playing(), false);
    EXPECT_EQ(current_animation->rects_count(), 6);

    sprite_sheet->SetAnimation(Engine::KnightAnimations::Death);
    current_animation = sprite_sheet->GetCurrentAnim();
    EXPECT_EQ(current_animation->rects_count(), 9);

    sprite_sheet->SetAnimation(Engine::KnightAnimations::Jump);
    current_animation = sprite_sheet->GetCurrentAnim();
    EXPECT_EQ(current_animation->rects_count(), 4);

    sprite_sheet->SetAnimation(Engine::KnightAnimations::Attack);
    current_animation = sprite_sheet->GetCurrentAnim();
    EXPECT_EQ(current_animation->rects_count(), 5);

    sprite_sheet->SetAnimation(Engine::KnightAnimations::Hurt);
    current_animation = sprite_sheet->GetCurrentAnim();
    EXPECT_EQ(current_animation->rects_count(), 3);
}