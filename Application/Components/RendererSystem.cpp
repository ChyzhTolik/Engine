#include "RendererSystem.hpp"
#include "Component.hpp"
#include "EntityMessages.hpp"
#include "SystemManager.hpp"

namespace Engine
{
    RendererSystem::RendererSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::Renderer, l_system_manager)
    {
        std::bitset<REQUIREMENTS_NUM> req;
        req.set((unsigned int)ComponentType::Position);
        req.set((unsigned int)ComponentType::SpriteSheet);
        m_requiredComponents.push_back(req);
        req.reset();
        m_system_manager->GetMessageHandler().Subscribe(EntityMessage::Direction_Changed,std::dynamic_pointer_cast<Observer>(shared_from_this()));
    }
    
    RendererSystem::~RendererSystem()
    {
    }

    void RendererSystem::Render(std::shared_ptr<Window> l_wind, unsigned int l_layer)
    {

    }
} // namespace Engine
