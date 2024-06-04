#pragma once

#include <bitset>
#include <vector>
#include <memory>

#include "Observer.hpp"
#include "EntityEvent.hpp"

namespace Engine
{
    enum class SystemType
    {
        Renderer,
        Movement,
        Collision,
        Control,
        State,
        SheetAnimation,
        All,
    };

    using SystemBitSet = std::bitset<static_cast<size_t>(SystemType::All)>;
    using Requirements = std::vector<SystemBitSet>;
    using EntityId = uint32_t;

    class SystemManager;

    class System : public Observer
    {
    public:
        explicit System(SystemType type, std::shared_ptr<SystemManager>& system_manager);
        virtual ~System();

        bool add_entity(EntityId id);
        bool has_entity(EntityId id);
        bool remove_entity(EntityId id);

        SystemType get_type() const;

        bool fits_requirements(const SystemBitSet& mask);
        void purge();

        virtual void update(float time) = 0;
        virtual void handle_event(EntityId entity, EntityEvent event) = 0;
    protected:
        SystemType m_type;
        std::shared_ptr<SystemManager> m_system_manager;
        Requirements m_required_components;
        std::vector<EntityId> m_entities;
    };
    
    
    
} // namespace Engine
