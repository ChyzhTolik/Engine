#pragma once

#include "System.hpp"
#include "SpriteSheet.hpp"

namespace Engine
{
    class AnimationSystem : public System, public std::enable_shared_from_this<AnimationSystem>
    {
    public:
        AnimationSystem(std::shared_ptr<SystemManager> l_system_manager);
        ~AnimationSystem();
        void Update(float l_dT) override;
        void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
        void Notify(const Message& l_message) override;
    private:
        void ChangeAnimation(const EntityId& l_entity, const AnimationType l_anim, bool l_play, bool l_loop);
    };    
} // namespace Engine
