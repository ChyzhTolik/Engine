#include <gtest/gtest.h>

#include "StateManager.hpp"
#include "EntitiesManager.hpp"
#include "StateSystem.hpp"
#include "StateComponent.hpp"
#include "SpriteSheetComponent.hpp"

class StateTestsFixture : public ::testing::Test
{
protected:
    std::shared_ptr<Engine::SystemManager> system_manager;
    std::shared_ptr<Engine::EntitiesManager> entities_manager;
    Engine::EntityId id;
    std::shared_ptr<Engine::StateSystem> state_system;
    std::shared_ptr<Engine::StateComponent> state_component;
    std::shared_ptr<Engine::SpriteSheetComponent<Engine::KnightAnimations>> sprite_sheet_component;

	void SetUp()
	{
		system_manager = std::make_shared<Engine::SystemManager>();
        system_manager->fill_systems();
        entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);
        system_manager->set_entity_manager(entities_manager);

        state_system = system_manager->get_system<Engine::StateSystem>(Engine::SystemType::State);

        id = entities_manager->add_entity("media/Entities/Knight_Char.json");
        state_component = entities_manager->get_component<Engine::StateComponent>(id, Engine::ComponentType::State);

        sprite_sheet_component = 
            entities_manager->get_component<Engine::SpriteSheetComponent<Engine::KnightAnimations>>(id, Engine::ComponentType::SpriteSheet);
        sprite_sheet_component->create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);
	}

	void TearDown()
	{
	}
};

TEST_F(StateTestsFixture, StateSystemUpdateTest)
{
    state_component->set_state(Engine::EntityState::Walking);
    state_system->update(5.f);

    system_manager->handle_events();
    EXPECT_EQ(state_component->get_state(), Engine::EntityState::Idle);
}

TEST_F(StateTestsFixture, StateSystemHandleEventTest)
{
    state_component->set_state(Engine::EntityState::Walking);

    state_system->handle_event(id, Engine::EntityEvent::Became_Idle);

    system_manager->handle_events();
    EXPECT_EQ(state_component->get_state(), Engine::EntityState::Idle);
}

TEST_F(StateTestsFixture, StateSystemNotifyTest)
{
    state_component->set_state(Engine::EntityState::Walking);

    Engine::Message message(Engine::EntityMessage::Move);
    message.m_receiver = id;
    message.m_data = Engine::Direction::Right;

    state_system->notify(message);

    system_manager->handle_events();
    EXPECT_EQ(state_component->get_state(), Engine::EntityState::Walking);

    message.m_data = Engine::EntityState::Dying;
    message.m_type = Engine::EntityMessage::Switch_State;
    state_system->notify(message);

    system_manager->handle_events();
    EXPECT_EQ(state_component->get_state(), Engine::EntityState::Dying);
}