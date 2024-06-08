#include <gtest/gtest.h>

#include "SharedContext.hpp"
#include "LayeredMap.hpp"
#include "MovementSystem.hpp"
#include "SpriteSheetComponent.hpp"

class MovementTestsFixture : public ::testing::Test
{
protected:
    std::shared_ptr<Engine::SystemManager> system_manager;
    std::shared_ptr<Engine::EntitiesManager> entities_manager;
    Engine::EntityId id;
    Engine::SharedContext context;
    std::shared_ptr<Engine::LayeredMap> map;
    std::shared_ptr<Engine::MovementSystem> movement_system;
    std::shared_ptr<Engine::MovableComponent> movable_component;
    std::shared_ptr<Engine::SpriteSheetComponent<Engine::KnightAnimations>> sprite_sheet_component;

	void SetUp()
	{
		system_manager = std::make_shared<Engine::SystemManager>();
        system_manager->fill_systems();
        entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);
        system_manager->set_entity_manager(entities_manager);
        context.m_entities_manager = entities_manager;
        context.m_system_manager = system_manager;

        map = std::make_shared<Engine::LayeredMap>(context);
        map->load_from_file("media/map/GameMap.json");

        movement_system = system_manager->get_system<Engine::MovementSystem>(Engine::SystemType::Movement);
        movement_system->set_map(map);

        id = entities_manager->add_entity("media/Entities/Knight_Char.json");
        movable_component = entities_manager->get_component<Engine::MovableComponent>(id, Engine::ComponentType::Movable);
        movable_component->set_acceleration({50.f, 100.f});

        sprite_sheet_component = 
            entities_manager->get_component<Engine::SpriteSheetComponent<Engine::KnightAnimations>>(id, Engine::ComponentType::SpriteSheet);
        sprite_sheet_component->create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);
	}

	void TearDown()
	{
	}
};

TEST_F(MovementTestsFixture, MovementSystemUpdateTest)
{
    movement_system->update(5.f);
    auto position_component = entities_manager->get_component<Engine::PositionComponent>(id, Engine::ComponentType::Position);

    EXPECT_EQ(position_component->get_position(),sf::Vector2f(1350.f, 1350.f));
}

TEST_F(MovementTestsFixture, MovementSystemHandleEventTest)
{
    Engine::EntityEvent event;
    movable_component->set_velocity({300.f,300.f});

    event = Engine::EntityEvent::Colliding_X;
    movement_system->handle_event(id, event);

    EXPECT_EQ(movable_component->get_velocity(),sf::Vector2f(0.f, 300.f));

    event = Engine::EntityEvent::Colliding_Y;
    movement_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_velocity(),sf::Vector2f(0.f, 0.f));

    event = Engine::EntityEvent::Moving_Left;
    movement_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_direction(),Engine::Direction::Left);
    EXPECT_EQ(sprite_sheet_component->get_sprite_sheet()->GetDirection(),Engine::Direction::Left);

    event = Engine::EntityEvent::Moving_Right;
    movement_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_direction(),Engine::Direction::Right);
    EXPECT_EQ(sprite_sheet_component->get_sprite_sheet()->GetDirection(),Engine::Direction::Right);

    event = Engine::EntityEvent::Moving_Up;
    movement_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_direction(),Engine::Direction::Up);
    EXPECT_EQ(sprite_sheet_component->get_sprite_sheet()->GetDirection(),Engine::Direction::Up);

    event = Engine::EntityEvent::Moving_Down;
    movement_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_direction(),Engine::Direction::Down);
    EXPECT_EQ(sprite_sheet_component->get_sprite_sheet()->GetDirection(),Engine::Direction::Down);
}

TEST_F(MovementTestsFixture, MovementSystemNotifyTest)
{
    Engine::Message message(Engine::EntityMessage::Is_Moving);
    message.m_receiver = id;
    movement_system->notify(message);

    system_manager->handle_events();

}