#pragma once

#include "System.hpp"

namespace Engine
{
    class SpriteSheetSystem : public System, public std::enable_shared_from_this<SpriteSheetSystem>
    {
    public:
        SpriteSheetSystem(std::shared_ptr<SystemManager> system_manager);
        ~SpriteSheetSystem();

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
    private:
        /* data */
    };
    
    
    
} // namespace Engine
