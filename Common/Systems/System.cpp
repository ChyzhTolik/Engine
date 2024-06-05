#include "System.hpp"

#include <algorithm>

namespace Engine
{
    System::System(SystemType type, std::shared_ptr<SystemManager>& system_manager) : m_type{type}, m_system_manager{system_manager}
    {
    }
    
    System::~System()
    {
        purge();
    }

    bool System::add_entity(EntityId id)
    {
        if (has_entity(id))
        {
            return false;
        }
        
        m_entities.emplace_back(id);

        return true;
    }

    bool System::has_entity(EntityId id)
    {
        auto it = std::find(m_entities.begin(),m_entities.end(),id);

        return it != m_entities.end();
    }

    bool System::remove_entity(EntityId id)
    {
        auto entity_itr = std::find_if(m_entities.begin(), m_entities.end(), [&id](EntityId entity_id)
        {
            return id == entity_id;
        });

        if (entity_itr == m_entities.end())
        {
            return false;
        }
        
        m_entities.erase(entity_itr);

        return false;
    }

    void System::purge()
    {
        m_entities.clear();
    }

    bool System::fits_requirements(const ComponentBitSet& mask)
    {
        return std::find_if(m_required_components.begin(),m_required_components.end(),[&mask](const ComponentBitSet& bitset)
        {
            ComponentBitSet m = mask & bitset;
            return m.any();
        })!= m_required_components.end();
    }
} // namespace Engine
