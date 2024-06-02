#include <gtest/gtest.h>

#include <EntitiesManager/EntitiesManager.hpp>
#include <Components/PositionComponent.hpp>
#include <Components/MovableComponent.hpp>
#include <Components/StateComponent.hpp>
#include <Components/ControllerComponent.hpp>

TEST(EntitiesManagerTests, TestAddEntity)
{
    std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
    Engine::EntitiesManager entities_manager(system_manager);
    Engine::ComponentBitSet mask;
    mask.set(static_cast<size_t>(Engine::ComponentType::Position));
    Engine::EntityId id = entities_manager.add_entity(mask);

    bool has = entities_manager.has_component(id,Engine::ComponentType::Position);
    EXPECT_EQ(has,true);
}

TEST(EntitiesManagerTests, TestRemoveComponent)
{
    std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
    Engine::EntitiesManager entities_manager(system_manager);
    Engine::ComponentBitSet mask;
    mask.set(static_cast<size_t>(Engine::ComponentType::Position));
    Engine::EntityId id = entities_manager.add_entity(mask);

    entities_manager.remove_component(id,Engine::ComponentType::Position);
    bool has = entities_manager.has_component(id,Engine::ComponentType::Position);
    EXPECT_EQ(has,false);
}

TEST(EntitiesManagerTests, TestGetComponent)
{
    std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
    Engine::EntitiesManager entities_manager(system_manager);
    Engine::ComponentBitSet mask;
    mask.set(static_cast<size_t>(Engine::ComponentType::Position));
    Engine::EntityId id = entities_manager.add_entity(mask);

    auto component = entities_manager.get_component<Engine::PositionComponent>(id, Engine::ComponentType::Position);
    EXPECT_NE(component,nullptr);

    component->set_position({2.f,3.f});
    EXPECT_EQ(component->get_position(), sf::Vector2f(2.f,3.f));
}

TEST(EntitiesManagerTests, TestRemoveEntity)
{
    std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
    Engine::EntitiesManager entities_manager(system_manager);
    Engine::ComponentBitSet mask;
    mask.set(static_cast<size_t>(Engine::ComponentType::Position));
    Engine::EntityId id = entities_manager.add_entity(mask);

    EXPECT_EQ(entities_manager.count(),1);

    auto result = entities_manager.remove_entity(id);
    EXPECT_EQ(result,true);
    EXPECT_EQ(entities_manager.count(),0);
}

TEST(EntitiesManagerTests, TestAddEntityFromFile)
{
    std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
    Engine::EntitiesManager entities_manager(system_manager);

    auto id = entities_manager.add_entity("media/Entities/Knight_Char.json");
    EXPECT_EQ(entities_manager.count(),1);

    auto pos_component = entities_manager.get_component<Engine::PositionComponent>(id, Engine::ComponentType::Position);
    EXPECT_EQ(pos_component->get_position(),sf::Vector2f(12.f,1.f));
    EXPECT_EQ(pos_component->get_elevation(),3);

    auto mov_component = entities_manager.get_component<Engine::MovableComponent>(id, Engine::ComponentType::Movable);
    EXPECT_EQ(mov_component->get_direction(), Engine::Direction::Up);
    EXPECT_EQ(mov_component->get_max_velocity(), 1000.f);
    EXPECT_EQ(mov_component->get_speed(), sf::Vector2f(100.f,100.f));

    auto state_component = entities_manager.get_component<Engine::StateComponent>(id, Engine::ComponentType::State);
    EXPECT_EQ(state_component->get_state(), Engine::EntityState::Hurt);

    auto controller_component = entities_manager.get_component<Engine::ControllerComponent>(id, Engine::ComponentType::Controller);
    EXPECT_EQ(controller_component->get_type(), Engine::ComponentType::Controller);
}