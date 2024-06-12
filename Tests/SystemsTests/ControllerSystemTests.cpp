#include <gtest/gtest.h>

#include "StateManager.hpp"
#include "EntitiesManager.hpp"
#include "ControllerSystem.hpp"
#include "ControllerComponent.hpp"
#include "SpriteSheetComponent.hpp"
#include "MovableComponent.hpp"

class ControllerTestsFixture : public ::testing::Test
{
protected:
    std::shared_ptr<Engine::SystemManager> system_manager;
    std::shared_ptr<Engine::EntitiesManager> entities_manager;
    Engine::EntityId id;
    std::shared_ptr<Engine::ControllerSystem> controller_system;
    std::shared_ptr<Engine::ControllerComponent> controller_component;
    std::shared_ptr<Engine::SpriteSheetComponent<Engine::KnightAnimations>> sprite_sheet_component;

	void SetUp()
	{
		system_manager = std::make_shared<Engine::SystemManager>();
        system_manager->fill_systems();
        entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);
        system_manager->set_entity_manager(entities_manager);

        controller_system = system_manager->get_system<Engine::ControllerSystem>(Engine::SystemType::Control);

        id = entities_manager->add_entity("media/Entities/Knight_Char.json");
        controller_component = entities_manager->get_component<Engine::ControllerComponent>(id, Engine::ComponentType::Controller);

        sprite_sheet_component = 
            entities_manager->get_component<Engine::SpriteSheetComponent<Engine::KnightAnimations>>(id, Engine::ComponentType::SpriteSheet);
        sprite_sheet_component->create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);
	}

	void TearDown()
	{
        
	}
};

TEST_F(ControllerTestsFixture, ControllerSystemHandleEventTest)
{
    auto movable_component = entities_manager->get_component<Engine::MovableComponent>(id, Engine::ComponentType::Movable);
    auto speed = movable_component->get_speed();

    Engine::EntityEvent event{Engine::EntityEvent::Moving_Right};
    controller_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_acceleration(), sf::Vector2f(speed.x, 0.f));

    event = Engine::EntityEvent::Moving_Left;
    controller_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_acceleration(), sf::Vector2f(0.f, 0.f));

    controller_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_acceleration(), sf::Vector2f(-speed.x, 0.f));

    event = Engine::EntityEvent::Moving_Up;
    controller_system->handle_event(id, event);
    EXPECT_EQ(movable_component->get_acceleration(), sf::Vector2f(-speed.x, -speed.y));
}