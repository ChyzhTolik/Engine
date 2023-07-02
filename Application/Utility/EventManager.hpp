#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <memory>

#include "ActionFunctinoid.hpp"
#include "EventDetails.hpp"

namespace Engine
{
    enum class EventType
    {
        KeyDown = sf::Event::KeyPressed,
        KeyUp = sf::Event::KeyReleased,
        MButtonDown = sf::Event::MouseButtonPressed,
        MButtonUp = sf::Event::MouseButtonReleased,
        MouseWheel = sf::Event::MouseWheelScrolled,
        WindowResized = sf::Event::Resized,
        GainedFocus = sf::Event::GainedFocus,
        LostFocus = sf::Event::LostFocus,
        MouseEntered = sf::Event::MouseEntered,
        MouseLeft = sf::Event::MouseLeft,
        Closed = sf::Event::Closed,
        TextEntered = sf::Event::TextEntered,
        Keyboard = sf::Event::Count + 1, Mouse, Joystick
    };

    struct EventInfo
    {
        EventInfo(){ m_code = 0; }
        EventInfo(int l_event){ m_code = l_event; }
        union
        {
            int m_code;
        };
    };

    using Events = std::vector<std::pair<EventType, EventInfo>>;

    struct Binding
    {
        Binding(const std::string& l_name) : m_name(l_name), m_details(l_name), c(0){}

        void BindEvent(EventType l_type, EventInfo l_info = EventInfo())
        {
            m_events.emplace_back(l_type, l_info);
        }

        Events m_events;
        std::string m_name;
        int c; // Count of events that are "happening".
        EventDetails m_details;
    };

    using Bindings = std::unordered_map<std::string, std::unique_ptr<Binding>>;

    // using ActionFunctinoids = std::unordered_map<std::string, std::unique_ptr<ActionFunctinoid>>;

    enum class StateType;
    // using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails&)>>;
    // using Callbacks = std::unordered_map<StateType, CallbackContainer>;

    using ActionContainer = std::unordered_map<std::string, std::unique_ptr<ActionFunctinoid>>;
    using Actions = std::unordered_map<StateType, ActionContainer>;

    class EventManager
    {
    private:
        Bindings m_bindings;
        StateType m_current_state;
        Actions m_actions;
        bool m_hasFocus;

        void LoadBindings();
    public:
        EventManager();
        ~EventManager();
        bool AddBinding(std::unique_ptr<Binding> l_binding);
        bool RemoveBinding(std::string l_name);

        void SetFocus(const bool& l_focus);

        void add_action(StateType l_state, std::string_view l_name, std::unique_ptr<ActionFunctinoid>&& l_action);
        bool remove_action(StateType l_state, std::string_view l_name);


        void HandleEvent(sf::Event& l_event);
        void Update();
        
        sf::Vector2i GetMousePos(sf::RenderWindow& l_wind)
        {
            return sf::Mouse::getPosition(l_wind);
        }

        void SetCurrentState(StateType l_state)
        {
            m_current_state = l_state;
        }
    };   
} // namespace Engine
