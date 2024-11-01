#pragma once

#include "States/BaseState.hpp"
#include "SharedContext.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>

namespace Engine
{
    enum class StateType
    {
        EnptyState,
        Intro = 1, 
        MainMenu, 
        Game, 
        Paused, 
        GameOver, 
        Credits
    };

    using StateContainer = std::vector<std::pair<StateType, std::unique_ptr<BaseState>>>;
    using TypeContainer = std::vector<StateType>;

    using StateFactory = std::unordered_map<StateType, std::unique_ptr<StateCreator>>;

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
        void set_game_callback(std::function<void()> callback);
                
    private:
        // Methods.
        void CreateState(const StateType& l_type);
        void RemoveState(const StateType& l_type);

        template<typename T, typename ...Args>
        void RegisterState(StateType l_type, Args&& ... args);
        // Members.
        SharedContext& m_shared;
        StateContainer m_states;
        TypeContainer m_toRemove;
        StateFactory m_stateFactory;
    };



    template<typename T, typename ...Args>
    void StateManager::RegisterState(StateType l_type, Args&& ... args)
    {
        m_stateFactory.insert({l_type, std::make_unique<T>(*this, std::forward<Args>(args)...)});
    }
    
} // namespace Engine