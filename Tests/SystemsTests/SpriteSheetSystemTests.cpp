#include <gtest/gtest.h>

#include "StateManager.hpp"
#include "EntitiesManager.hpp"
#include "SpriteSheetSystem.hpp"
#include "SpriteSheetComponent.hpp"
#include "AnimationsToStateConverter.hpp"

class SpriteSheetSystemTestsFixture : public ::testing::Test
{
protected:
    std::shared_ptr<Engine::SystemManager> system_manager;
    std::shared_ptr<Engine::EntitiesManager> entities_manager;
    Engine::EntityId id;
    std::shared_ptr<Engine::SpriteSheetSystem> sprite_sheet_system;
    std::shared_ptr<Engine::SpriteSheetComponent<Engine::KnightAnimations>> sprite_sheet_component;
    std::shared_ptr<Engine::SpriteSheetTemplate<Engine::KnightAnimations>> sprite_sheet;

	void SetUp()
	{
		system_manager = std::make_shared<Engine::SystemManager>();
        system_manager->fill_systems();
        entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);
        system_manager->set_entity_manager(entities_manager);
        
        id = entities_manager->add_entity("media/Entities/Knight_Char.json");

        sprite_sheet_component = 
            entities_manager->get_component<Engine::SpriteSheetComponent<Engine::KnightAnimations>>(id, Engine::ComponentType::SpriteSheet);
        sprite_sheet_component->create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);

        sprite_sheet_system = system_manager->get_system<Engine::SpriteSheetSystem>(Engine::SystemType::SheetAnimation);
        sprite_sheet = std::dynamic_pointer_cast<Engine::SpriteSheetTemplate<Engine::KnightAnimations>>(sprite_sheet_component->get_sprite_sheet());

        Engine::ChangeAnimationCallback callback = [this](Engine::EntityState state, bool play, bool loop)
        {
            sprite_sheet->SetAnimation(Engine::AnimationsToStateConverter::convert(state), play, loop);
        };

        sprite_sheet_system->set_change_animation_callback(id, callback);
	}

	void TearDown()
	{
	}
};

TEST_F(SpriteSheetSystemTestsFixture, SpriteSheetSystemUpdateTest)
{
    sprite_sheet->SetAnimation(Engine::KnightAnimations::Attack, false, true);
    sprite_sheet_system->update(2.f);
    EXPECT_EQ(sprite_sheet->get_current_type(), Engine::KnightAnimations::Idle);

    sprite_sheet->SetAnimation(Engine::KnightAnimations::Attack, true, true);
    sprite_sheet_system->update(2.f);
    EXPECT_EQ(sprite_sheet->get_current_type(), Engine::KnightAnimations::Attack);
}

TEST_F(SpriteSheetSystemTestsFixture, SpriteSheetSystemHandleEventTest)
{
    Engine::Message message{Engine::EntityMessage::State_Changed};
    message.m_receiver = id;
    message.m_data = Engine::EntityState::Jumping;

    sprite_sheet_system->notify(message);

    EXPECT_EQ(sprite_sheet->get_current_type(), Engine::KnightAnimations::Jump);
}