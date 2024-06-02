#include <gtest/gtest.h>

#include <Components/PositionComponent.hpp>
#include <Components/MovableComponent.hpp>
#include <Components/StateComponent.hpp>

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