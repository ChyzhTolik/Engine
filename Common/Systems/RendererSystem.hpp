#pragma once

#include "System.hpp"
#include "Direction.hpp"
#include "Window.hpp"

namespace Engine
{
    class RendererSystem : public System, public std::enable_shared_from_this<RendererSystem>
    {
    public:
        RendererSystem(std::shared_ptr<SystemManager> system_manager);
        ~RendererSystem();

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
        void render(std::shared_ptr<Window> window, uint16_t layer);
    private:
        void sort_drawables();
        void set_sprite_sheet_direction(EntityId id, Direction dir);
    };
    
    
    
} // namespace Engine
