#pragma once

#include <vector>
#include <cstdint>
#include <bitset>
#include <memory>
#include <variant>

namespace Engine
{
    const uint32_t REQUIREMENTS_NUM = 20;

    class SystemManager;

    enum class SystemType
    {
        Renderer = 0, 
        Movement, 
        Collision, 
        Control, 
        State, 
        SheetAnimation
    };

    enum class EntityEvent
    {
        Spawned, Despawned, Colliding_X, Colliding_Y,
        Moving_Left, Moving_Right, Moving_Up, Moving_Down,
        Elevation_Change, Became_Idle, Began_Moving
    };

    using MessageType = uint32_t;
    struct TwoFloats{ float m_x; float m_y; };

    struct Message
    {
        Message(const MessageType& l_type) : m_type(l_type){}
        MessageType m_type;
        int m_sender;
        int m_receiver;
        std::variant<TwoFloats, bool, int> m_info;
    };

    class Observer
    {
    public:
        virtual ~Observer(){}
        virtual void Notify(const Message& l_message) = 0;
    };

    using ObserverContainer = std::vector<std::shared_ptr<Observer>>;

    class Communicator
    {
    public:
        ~Communicator()
        { 
            m_observers.clear(); 
        }

        bool AddObserver(std::shared_ptr<Observer> l_observer)
        {
            if (HasObserver(l_observer))
            { 
                return false; 
            }

            m_observers.emplace_back(l_observer);
            return true;
        }

        bool RemoveObserver(std::shared_ptr<Observer> l_observer)
        {
            auto observer = std::find_if(m_observers.begin(),m_observers.end(), [&l_observer](std::shared_ptr<Observer> o)
            {
                return o == l_observer; 
            });
            
            if (observer == m_observers.end())
            { 
                return false; 
            }

            m_observers.erase(observer);
            return true;
        }

        bool HasObserver(const std::shared_ptr<Observer> l_observer)
        {
            return (std::find_if(m_observers.begin(), m_observers.end(), 
            [&l_observer](std::shared_ptr<Observer> o)
            {
                return o == l_observer;
            }) != m_observers.end());
        }

        void Broadcast(const Message& l_msg)
        {
            for(auto& itr : m_observers){ itr->Notify(l_msg); }
        }
    private:
        ObserverContainer m_observers;
    };

    using EntityId = uint32_t;
    using EntityList = std::vector<EntityId>;
    using Requirements = std::vector<std::bitset<REQUIREMENTS_NUM>>;

    class System : public Observer
    {
    public:
        System(SystemType l_type, std::shared_ptr<SystemManager> l_system_manager);
        virtual ~System();

        bool AddEntity(const EntityId& l_entity);
        bool HasEntity(const EntityId& l_entity);
        bool RemoveEntity(const EntityId& l_entity);
        SystemType get_type();
        bool FitsRequirements(const std::bitset<REQUIREMENTS_NUM>& l_bits);
        void Purge();
        virtual void Update(float l_dT) = 0;
        virtual void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) = 0;

    protected:
        std::shared_ptr<SystemManager> m_system_manager;
        SystemType m_type;

        Requirements m_requiredComponents;
        EntityList m_entities;
    };    
} // namespace Engine
