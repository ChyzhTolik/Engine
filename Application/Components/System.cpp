#include "System.hpp"

namespace Engine
{
    System::System(SystemType l_type, std::shared_ptr<SystemManager> l_system_manager) : m_system_manager(l_system_manager), m_type(l_type)
    {
    }
    
    System::~System()
    {
        Purge();
    }

    bool System::AddEntity(const EntityId& l_entity)
    {
        if (HasEntity(l_entity))
        { 
            return false; 
        }

        m_entities.emplace_back(l_entity);
        return true;
    }

    bool System::HasEntity(const EntityId& l_entity)
    {
        return std::find(m_entities.begin(), m_entities.end(), l_entity) != m_entities.end();
    }

    bool System::RemoveEntity(const EntityId& l_entity)
    {
        auto entity = std::find_if(m_entities.begin(), m_entities.end(), [&l_entity](EntityId& id){ return id == l_entity; });

        if (entity == m_entities.end())
        { 
            return false; 
        }

        m_entities.erase(entity);
        return true;
    }

    SystemType System::get_type()
    {
        return m_type;
    }

    bool System::FitsRequirements(const std::bitset<REQUIREMENTS_NUM>& l_bits)
    {
        return std::find_if(m_requiredComponents.begin(),m_requiredComponents.end(), [&l_bits](std::bitset<REQUIREMENTS_NUM>& b)
        {
            return b == l_bits;
        }) != m_requiredComponents.end();
    }

    void System::Purge()
    {
        m_entities.clear();
    }
} // namespace Engine
