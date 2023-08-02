#include "AnimationSystem.hpp"

#include "Component.hpp"
#include "SystemManager.hpp"
#include "EntitiesManager.hpp"
#include "SpriteSheetComponent.hpp"
#include "StateComponent.hpp"

namespace Engine
{
    AnimationSystem::AnimationSystem(std::shared_ptr<SystemManager> l_system_manager) : System(SystemType::SheetAnimation, l_system_manager)
    {
        std::bitset<REQUIREMENTS_NUM> req;
        req.set((unsigned int)ComponentType::SpriteSheet);
        req.set((unsigned int)ComponentType::State);
        m_requiredComponents.push_back(req);
        m_system_manager->GetMessageHandler().Subscribe(EntityMessage::State_Changed,shared_from_this());
    }
    
    AnimationSystem::~AnimationSystem()
    {
    }

    void AnimationSystem::Update(float l_dT)
    {
        auto entities = m_system_manager->GetEntityManager();

        for(auto &entity : m_entities)
        {
            auto sheet = entities->GetComponent<SpriteSheetComponent>(entity, ComponentType::SpriteSheet);
            auto state = entities->GetComponent<StateComponent>(entity, ComponentType::State);
            sheet->GetSpriteSheet()->Update(l_dT);
            const std::string& animName = sheet->GetSpriteSheet()->GetCurrentAnim()->get_name();

            if(animName == "Attack")
            {
                if(!sheet->GetSpriteSheet()->GetCurrentAnim()->is_playing())
                {
                    Message msg((MessageType)EntityMessage::Switch_State);
                    msg.m_receiver = entity;
                    msg.m_info = (int)EntityState::Idle;
                    m_system_manager->GetMessageHandler().Dispatch(msg);
                } 
                else if(sheet->GetSpriteSheet()->GetCurrentAnim()->IsInAction())
                {
                    Message msg((MessageType)EntityMessage::Attack_Action);
                    msg.m_sender = entity;
                    m_system_manager->GetMessageHandler().Dispatch(msg);
                }
            } 
            else if(animName == "Death" && !sheet->GetSpriteSheet()->GetCurrentAnim()->is_playing())
            {
                Message msg((MessageType)EntityMessage::Dead);
                msg.m_receiver = entity;
                m_system_manager->GetMessageHandler().Dispatch(msg);
            }
        }
    }

    void AnimationSystem::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event)
    {

    }

    void AnimationSystem::Notify(const Message& l_message)
    {
        if(HasEntity(l_message.m_receiver))
        {
            EntityMessage m = (EntityMessage)l_message.m_type;
            switch(m)
            {
                case EntityMessage::State_Changed:
                {
                    EntityState s = EntityState(std::get<int>(l_message.m_info));
                    switch(s)
                    {
                        case EntityState::Idle:
                            ChangeAnimation(l_message.m_receiver,AnimationType::Idle,true,true);
                        break;

                        case EntityState::Walking:
                            ChangeAnimation(l_message.m_receiver,AnimationType::Running,true,true);
                        break;

                        case EntityState::Attacking:
                            ChangeAnimation(l_message.m_receiver, AnimationType::Attacking,true,false);
                        break;

                        case EntityState::Hurt: 
                        break;
                        
                        case EntityState::Dying:
                            ChangeAnimation(l_message.m_receiver, AnimationType::Death,true,false);
                        break;
                    }
                }
                break;
            }
        }
    }

    void AnimationSystem::ChangeAnimation(const EntityId& l_entity, const AnimationType l_anim, bool l_play, bool l_loop)
    {
        auto sheet = m_system_manager->GetEntityManager()-> GetComponent<SpriteSheetComponent>(l_entity,ComponentType::SpriteSheet);
        sheet->GetSpriteSheet()->SetAnimation(l_anim,l_play,l_loop);
    }
} // namespace Engine
