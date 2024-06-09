#pragma once

#include "System.hpp"

#include <functional>

namespace Engine
{
    using ChangeAnimationCallback = std::function<void(EntityState, bool, bool)>;

    class SpriteSheetSystem : public System, public std::enable_shared_from_this<SpriteSheetSystem>
    {
    public:
        SpriteSheetSystem(std::shared_ptr<SystemManager> system_manager);
        ~SpriteSheetSystem();

        void subscribe() override;

        void update(float time) override;
        void handle_event(EntityId entity, EntityEvent event) override;
        void notify(const Message& message) override;
        void set_change_animation_callback(EntityId id, ChangeAnimationCallback callback);
    private:
        std::unordered_map<EntityId,ChangeAnimationCallback> m_callbacks;
    };
} // namespace Engine
