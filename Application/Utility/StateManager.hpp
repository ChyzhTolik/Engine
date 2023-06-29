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

    class StateCreator
    {
    public:
        StateCreator() = default;
        virtual ~StateCreator(){};
        virtual std::shared_ptr<BaseState> create(StateManager& state_manager) = 0;
    };

    using StateContainer = std::vector<std::pair<StateType, std::shared_ptr<BaseState>&>>;
    using TypeContainer = std::vector<StateType>;

    using StateFactory = std::unordered_map<StateType, std::function<std::shared_ptr<BaseState>(void)>>;

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

        template<typename T, typename ...Args>
        std::shared_ptr<BaseState> RegisterState(const StateType& l_type, Args&& ... args);
        // Members.
        SharedContext& m_shared;
        StateContainer m_states;
        TypeContainer m_toRemove;
        StateFactory m_stateFactory;
    };

    // template <typename ...Args>
    // void use(Args... args)
    // {
    //     f(std::forward<Args>(args)...);
    // }

    // template <typename ... Args>
    // auto f(Args&& ... args)
    // {
    //     return [... args = std::forward<Args>(args)]{
    //         // use args
    //     };
    // }

    // template <typename ... Args>
    // auto f(Args&& ... args){
    //     return [args = std::make_tuple(std::forward<Args>(args) ...)]()mutable{
    //         return std::apply([](auto&& ... args){
    //             // use args
    //         }, std::move(args));
    //     };
    // }

    // template <typename... Args>
    // auto f(Args&&... args){

    //     auto functional = [](auto&&... args) { /* lambda body */ };
    //     return std::bind(std::move(functional), std::forward<Args>(args)...);
    // }


    template<typename T, typename ...Args>
    std::shared_ptr<BaseState> StateManager::RegisterState(const StateType& l_type, Args&& ... args)
    {
        // m_stateFactory[l_type] = [this, args = std::make_tuple(std::forward<Args>(args) ...)]() -> std::shared_ptr<BaseState>
        // {
        //     return std::make_shared<T>(*this, std::forward<Args>(args)...);
        // };
        return std::make_shared<T>(*this, std::forward<Args>(args)...);

    }
    
} // namespace Engine
