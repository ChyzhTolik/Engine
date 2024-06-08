#include <gtest/gtest.h>

#include <Components/PositionComponent.hpp>
#include <Components/MovableComponent.hpp>
#include <Components/StateComponent.hpp>
#include <Components/SpriteSheetComponent.hpp>
#include <Animations/Anim_Directional.hpp>
#include <Components/CollidableComponent.hpp>

#include <AnimationTypes.hpp>

TEST(ComponentsTests, PositioinComponentTests)
{
    Engine::PositionComponent pos_component;

    Engine::PositionInfo pos_info{{1.3f,2.5f},6};
    json jey;
    jey = Engine::PosComponentTestHelper::get_json(pos_info);

    pos_component.read_in(jey);
    EXPECT_EQ(pos_component.get_position(), sf::Vector2f(1.3f,2.5f));
    EXPECT_EQ(pos_component.get_old_position(), sf::Vector2f(0.f,0.f));
    EXPECT_EQ(pos_component.get_elevation(), 6);

    pos_component.set_position({2.f,3.f});
    EXPECT_EQ(pos_component.get_old_position(), sf::Vector2f(1.3f,2.5f));
    EXPECT_EQ(pos_component.get_position(), sf::Vector2f(2.f,3.f));

    pos_component.set_elevation(5);
    EXPECT_EQ(pos_component.get_elevation(), 5);

    pos_component.move_by({10.f,10.f});
    EXPECT_EQ(pos_component.get_old_position(), sf::Vector2f(2.f,3.f));
    EXPECT_EQ(pos_component.get_position(), sf::Vector2f(12.f,13.f));
}

TEST(ComponentsTests, MovableComponentTests)
{
    Engine::MovableComponent mov_component;
    json jey;
    Engine::MovableInfo mov_info{1000.f,{20.f,20.f},Engine::Direction::Right};

    jey = Engine::MovComponentTestHelper::get_json(mov_info);

    mov_component.read_in(jey);
    EXPECT_EQ(mov_component.get_direction(), Engine::Direction::Right);
    EXPECT_EQ(mov_component.get_acceleration(), sf::Vector2f(0.f,0.f));
    EXPECT_EQ(mov_component.get_max_velocity(), 1000.f);
    EXPECT_EQ(mov_component.get_speed(), sf::Vector2f(20.f,20.f));
    EXPECT_EQ(mov_component.get_velocity(), sf::Vector2f(0.f,0.f));

    mov_component.accelerate({100.f, 100.f});
    EXPECT_EQ(mov_component.get_acceleration(), sf::Vector2f(100.f,100.f));

    mov_component.add_velocity({50.f, 50.f});
    EXPECT_EQ(mov_component.get_velocity(), sf::Vector2f(50.f,50.f));

    mov_component.add_velocity({5000.f, 5000.f});
    EXPECT_EQ(mov_component.get_velocity(), sf::Vector2f(mov_component.get_max_velocity(),mov_component.get_max_velocity()));

    mov_component.move(Engine::Direction::Up);
    EXPECT_EQ(mov_component.get_acceleration(), sf::Vector2f(100.f,80.f));
    EXPECT_EQ(mov_component.get_direction(), Engine::Direction::Up);

    mov_component.move(Engine::Direction::Down);
    EXPECT_EQ(mov_component.get_acceleration(), sf::Vector2f(100.f,100.f));
    EXPECT_EQ(mov_component.get_direction(), Engine::Direction::Down);

    mov_component.move(Engine::Direction::Left);
    EXPECT_EQ(mov_component.get_acceleration(), sf::Vector2f(80.f,100.f));
    EXPECT_EQ(mov_component.get_direction(), Engine::Direction::Left);

    mov_component.move(Engine::Direction::Right);
    EXPECT_EQ(mov_component.get_acceleration(), sf::Vector2f(100.f,100.f));
    EXPECT_EQ(mov_component.get_direction(), Engine::Direction::Right);

    mov_component.add_velocity({-900.f, -900.f});
    mov_component.apply_friction({30.f,30.f});
    EXPECT_EQ(mov_component.get_velocity(), sf::Vector2f(70.f,70.f));

    mov_component.apply_friction({-330.f,0.f});
    EXPECT_EQ(mov_component.get_velocity(), sf::Vector2f(0.f,70.f));
}

TEST(ComponentsTests, StateComponentTests)
{
    Engine::StateComponent state_component;

    Engine::StateInfo state_info{Engine::EntityState::Attacking};
    json jey;
    jey = Engine::StateComponentTestHelper::get_json(state_info);

    state_component.read_in(jey);
    EXPECT_EQ(state_component.get_state(), Engine::EntityState::Attacking);

    state_component.set_state(Engine::EntityState::Idle);
    EXPECT_EQ(state_component.get_state(), Engine::EntityState::Idle);
}

TEST(ComponentsTests, SpriteSheetComponentTests)
{
    Engine::Configuration::Initialize();

    Engine::SpriteSheetComponent<Engine::KnightAnimations> sprite_sheet_component;

    Engine::SpriteSheetInfo sheet_info{"media/Animations/Knight_Animations.json"};
    json jey;
    jey = Engine::SpriteSheetComponentTestHelper::get_json(sheet_info);

    sprite_sheet_component.read_in(jey);
    sprite_sheet_component.create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);
    auto sprite_sheet = std::dynamic_pointer_cast<Engine::SpriteSheetTemplate<Engine::KnightAnimations>>(sprite_sheet_component.get_sprite_sheet());
    sprite_sheet->SetAnimation(Engine::KnightAnimations::Idle);
    sprite_sheet_component.get_sprite_sheet()->GetCurrentAnim()->Play();
    sprite_sheet_component.get_sprite_sheet()->GetCurrentAnim()->SetLooping(true);
    auto current_animation = sprite_sheet_component.get_sprite_sheet()->GetCurrentAnim();
    EXPECT_EQ(current_animation->is_playing(), true);
    EXPECT_EQ(current_animation->rects_count(), 8);
}

TEST(ComponentsTests, CollidableComponentTests)
{
    Engine::CollidableComponent collidable_component;

    Engine::CollidableInfo collidable_info{{{},{32.f,32.f}},{5.f,10.f},Engine::Origin::TopLeft};
    json jey;
    jey = Engine::CollidableComponentTestHelper::get_json(collidable_info);

    collidable_component.read_in(jey);
    
    EXPECT_EQ(collidable_component.get_colliding_on_x(), false);
    EXPECT_EQ(collidable_component.get_colliding_on_y(), false);
    EXPECT_EQ(collidable_component.get_offset(), sf::Vector2f(5.f,10.f));
    EXPECT_EQ(collidable_component.get_origin(), Engine::Origin::TopLeft);
    EXPECT_EQ(collidable_component.get_box_size(), sf::Vector2f(32.f,32.f));

    collidable_component.collide_on_x();
    collidable_component.collide_on_y();
    collidable_component.set_origin(Engine::Origin::AbsCenter);
    collidable_component.set_size({40.f,40.f});
    collidable_component.set_position({100.f,100.f});


    EXPECT_EQ(collidable_component.get_colliding_on_x(), true);
    EXPECT_EQ(collidable_component.get_colliding_on_y(), true);
    EXPECT_EQ(collidable_component.get_origin(), Engine::Origin::AbsCenter);
    EXPECT_EQ(collidable_component.get_box_size(), sf::Vector2f(40.f,40.f));
    EXPECT_EQ(collidable_component.get_position(), sf::Vector2f(85.f,90.f));

    collidable_component.set_origin(Engine::Origin::MidBottom);
    collidable_component.set_position({100.f,100.f});
    EXPECT_EQ(collidable_component.get_position(), sf::Vector2f(85.f,70.f));

    collidable_component.set_origin(Engine::Origin::TopLeft);
    collidable_component.set_position({100.f,100.f});
    EXPECT_EQ(collidable_component.get_position(), sf::Vector2f(105.f,110.f));
}