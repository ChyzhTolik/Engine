#pragma once

#include "BaseState.hpp"
#include "SharedContext.hpp"
#include <vector>
#include <memory>
// #include <concepts>

namespace Engine
{
    enum class StateType
    {
        Intro = 1, 
        MainMenu, 
        Game, 
        Paused, 
        GameOver, 
        Credits
    };

    using StateContainer = std::vector<std::pair<StateType, std::unique_ptr<BaseState>>>;
    using TypeContainer = std::vector<StateType>;

    using StateFactory = std::unordered_map<StateType, std::function<std::unique_ptr<BaseState>(void)>>;

    class StateManager
    {
    public:
        StateManager(SharedContext& l_shared);
        ~StateManager();
        void Update(const sf::Time& l_time);
        void Draw();
        void ProcessRequests();
        SharedContext& GetContext();
        bool HasState(const StateType& l_type);
        void SwitchTo(const StateType& l_type);
        void Remove(const StateType& l_type);
        
    private:
        // Methods.
        void CreateState(const StateType& l_type);
        void RemoveState(const StateType& l_type);

        template<typename T>
        void RegisterState(const StateType& l_type);
        // Members.
        SharedContext& m_shared;
        StateContainer m_states;
        TypeContainer m_toRemove;
        StateFactory m_stateFactory;
    };

    template<typename T>
    void StateManager::RegisterState(const StateType& l_type)
    {
        m_stateFactory[l_type] = [this]() -> std::unique_ptr<BaseState>
        {
            return std::make_unique<T>(*this);
        };
    }
    
} // namespace Engine
