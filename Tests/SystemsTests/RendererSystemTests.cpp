#include <gtest/gtest.h>

#include <Systems/RendererSystem.hpp>
#include <EntitiesManager/EntitiesManager.hpp>
#include <Systems/SystemManager.hpp>
#include <AnimationTypes.hpp>
#include <Components/SpriteSheetComponent.hpp>
#include <Components/PositionComponent.hpp>
#include <Systems/Message.hpp>

class SystemsTestsFixture : public ::testing::Test
{
protected:
	void SetUp()
	{
		std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
        system_manager->fill_systems();
        std::shared_ptr<Engine::EntitiesManager> entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);

        auto id = entities_manager->add_entity("media/Entities/Knight_Char.json");
	}
	void TearDown()
	{
	}
};

TEST(SystemsTests, RendererSystemUpdateTest)
{
    std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
    system_manager->fill_systems();
    std::shared_ptr<Engine::EntitiesManager> entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);

    auto id = entities_manager->add_entity("media/Entities/Knight_Char.json");
    EXPECT_EQ(entities_manager->count(),1);

    system_manager->set_entity_manager(entities_manager);
    auto sprite_sheet_component = 
        entities_manager->get_component<Engine::SpriteSheetComponent<Engine::KnightAnimations>>(id, Engine::ComponentType::SpriteSheet);
    sprite_sheet_component->create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);

    auto renderer_system = system_manager->get_system<Engine::RendererSystem>(Engine::SystemType::Renderer);

    auto pos_component = entities_manager->get_component<Engine::PositionComponent>(id,Engine::ComponentType::Position);
    pos_component->set_position({200.f,200.f});

    renderer_system->update(0.f);
    auto new_pos = sprite_sheet_component->get_sprite_sheet()->GetSpritePosition();

    EXPECT_EQ(new_pos, sf::Vector2f(200.f,200.f));
}

TEST(SystemsTests, RendererSystemNotifyTest)
{
    std::shared_ptr<Engine::SystemManager> system_manager = std::make_shared<Engine::SystemManager>();
    system_manager->fill_systems();
    std::shared_ptr<Engine::EntitiesManager> entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);

    auto id = entities_manager->add_entity("media/Entities/Knight_Char.json");
    EXPECT_EQ(entities_manager->count(),1);

    system_manager->set_entity_manager(entities_manager);
    auto sprite_sheet_component = 
        entities_manager->get_component<Engine::SpriteSheetComponent<Engine::KnightAnimations>>(id, Engine::ComponentType::SpriteSheet);
    sprite_sheet_component->create<Engine::Anim_Directional>(Engine::Configuration::Textures::Knigth);
    sprite_sheet_component->get_sprite_sheet()->SetDirection(Engine::Direction::Right);

    auto renderer_system = system_manager->get_system<Engine::RendererSystem>(Engine::SystemType::Renderer);

    Engine::Message message(Engine::EntityMessage::Direction_Changed);
    message.m_receiver = id;
    message.m_data = Engine::Direction::Left;

    renderer_system->notify(message);

    EXPECT_EQ(sprite_sheet_component->get_sprite_sheet()->GetDirection(), Engine::Direction::Left);
}