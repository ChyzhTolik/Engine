#pragma once

#include "System.hpp"
#include "Window.hpp"
#include "Direction.hpp"

namespace Engine
{
    class RendererSystem : public System, public std::enable_shared_from_this<RendererSystem>
    {
    public:
        RendererSystem(std::shared_ptr<SystemManager> l_system_manager);
        virtual ~RendererSystem();
        void Render(std::shared_ptr<Window> l_wind, unsigned int l_layer);
        virtual void Update(float l_dT) override;
        virtual void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
        virtual void Notify(const Message& l_message) override;

    private:
        void SetSheetDirection(const EntityId l_entity, const Direction l_dir);
        void SortDrawables();
    };
    
} // namespace Engine
