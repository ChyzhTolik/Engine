#include <gtest/gtest.h>

#include <Systems/SystemManager.hpp>
#include <EntitiesManager/EntitiesManager.hpp>
#include <Systems/RendererSystem.hpp>

TEST(SystemManagerTests, PositioinComponentTests)
{
    std::shared_ptr<Engine::SystemManager>system_manager = std::make_shared<Engine::SystemManager>();

    std::shared_ptr<Engine::EntitiesManager> entities_manager = std::make_shared<Engine::EntitiesManager>(system_manager);

    auto id = entities_manager->add_entity("media/Entities/Knight_Char.json");
    EXPECT_EQ(entities_manager->count(),1);

    system_manager->set_entity_manager(entities_manager);

    system_manager->add_event(id, Engine::EntityEvent::Moving_Right);
    auto renderer_system = system_manager->get_system<Engine::RendererSystem>(Engine::SystemType::Renderer);

    
}