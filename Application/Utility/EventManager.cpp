#include "EventManager.hpp"

#include <fstream>
#include <iostream>

namespace Engine
{
    EventManager::EventManager(): m_hasFocus(true)
    { 
        LoadBindings(); 
    }

    EventManager::~EventManager()
    {
    }

    bool EventManager::AddBinding(std::unique_ptr<Binding> l_binding)
    {
        if (m_bindings.find(l_binding->m_name) != m_bindings.end())
        {
            return false;
        }
        
        return m_bindings.emplace(l_binding->m_name,std::move(l_binding)).second;
    }

    bool EventManager::RemoveBinding(std::string l_name)
    {
        auto itr = m_bindings.find(l_name);

        if (itr == m_bindings.end())
        { 
            return false;
        }

        m_bindings.erase(itr);
        return true;
    }

    void EventManager::HandleEvent(sf::Event& l_event)
    {
        // Handling SFML events.
        for (auto &b_itr : m_bindings)
        {
            auto& bind = b_itr.second;

            for (auto &e_itr : bind->m_events)
            {
                EventType sfmlEvent = static_cast<EventType>(l_event.type);

                if (e_itr.first != sfmlEvent)
                { 
                    continue; 
                }

                if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
                {
                    if (e_itr.second.m_code == l_event.key.code)
                    {
                        // Matching event/keystroke.
                        // Increase count.
                        if (bind->m_details.m_keyCode != -1)
                        {
                            bind->m_details.m_keyCode = e_itr.second.m_code;
                        }
                        
                        ++(bind->c);
                        break;
                    }
                } 
                else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
                {
                    if (e_itr.second.m_code == l_event.mouseButton.button)
                    {
                        // Matching event/keystroke.
                        // Increase count.
                        bind->m_details.m_mouse.x = l_event.mouseButton.x;
                        bind->m_details.m_mouse.y = l_event.mouseButton.y;

                        if (bind->m_details.m_keyCode != -1)
                        {
                            bind->m_details.m_keyCode = e_itr.second.m_code;
                        }

                        ++(bind->c);
                        break;
                    }
                } 
                else 
                {
                    // No need for additional checking.
                    if (sfmlEvent == EventType::MouseWheel)
                    {
                        bind->m_details.m_mouseWheelDelta =
                        l_event.mouseWheelScroll.delta;
                    } 
                    else if (sfmlEvent == EventType::WindowResized)
                    {
                        bind->m_details.m_size.x = l_event.size.width;
                        bind->m_details.m_size.y = l_event.size.height;
                    } else if (sfmlEvent == EventType::TextEntered)
                    {
                        bind->m_details.m_textEntered = l_event.text.unicode;
                    }

                    ++(bind->c);
                }
            }
        }
    }

    void EventManager::Update()
    {
        if (!m_hasFocus)
        { 
            return; 
        }

        for (auto &b_itr : m_bindings)
        {
            auto& bind = b_itr.second;

            for (auto &e_itr : bind->m_events)
            {
                switch (e_itr.first){
                    case(EventType::Keyboard) :
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code)))
                        {
                            if (bind->m_details.m_keyCode != -1)
                            {
                                bind->m_details.m_keyCode = e_itr.second.m_code;
                            }

                            ++(bind->c);
                        }
                    }
                break;

                    case(EventType::Mouse) :
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code)))
                        {
                            if (bind->m_details.m_keyCode != -1)
                            {
                                bind->m_details.m_keyCode = e_itr.second.m_code;
                            }

                            ++(bind->c);
                        }
                    }
                break;
                    case(EventType::Joystick) :
                // Up for expansion.
                break;
                }
            }

            if (bind->m_events.size() == bind->c)
            {
                // auto callItr = m_callbacks.find(bind->m_name);

                // if(callItr != m_callbacks.end())
                // {
                //     callItr->second(bind->m_details);
                // }

                auto state_action = m_actions.find(m_current_state);
                auto other_actions = m_actions.find(StateType(0));

                if (state_action != m_actions.end())
                {
                    auto callItr = state_action->second.find(bind->m_name);

                    if (callItr != state_action->second.end())
                    {
                        callItr->second->execute();
                    }
                }

                if (other_actions != m_actions.end())
                {
                    auto callItr = other_actions->second.find(bind->m_name);

                    if (callItr != other_actions->second.end())
                    {
                        callItr->second->execute();
                    }
                }
            }

            bind->c = 0;
            bind->m_details.Clear();
        }
    }

    void EventManager::LoadBindings()
    {
        std::string delimiter = ":";

        std::ifstream bindings;
#ifdef WIN32
        bindings.open("media/keys.cfg");
#elif UNIX
        bindings.open("/home/achyzh/TestProjects/Engine/Application/keys.cfg");

#endif // WIN32


        if (!bindings.is_open())
        { 
            std::cout << "! Failed loading keys.cfg." << std::endl; return; 
        }

        std::string line;
        while (std::getline(bindings, line))
        {
            std::stringstream keystream(line);
            std::string callbackName;
            keystream >> callbackName;
            std::unique_ptr<Binding> bind = std::make_unique<Binding>(callbackName);

            while (!keystream.eof())
            {
                std::string keyval;
                keystream >> keyval;
                if(keystream.fail()) {
                    keystream.clear();
                    break;
                }
                int start = 0;
                int end = keyval.find(delimiter);

                if (end == std::string::npos)
                { 
                    break; 
                }

                EventType type = EventType(stoi(keyval.substr(start, end - start)));
                int code = stoi(keyval.substr(end + delimiter.length(),
                    keyval.find(delimiter, end + delimiter.length())));
                EventInfo eventInfo;
                eventInfo.m_code = code;

                bind->BindEvent(type, eventInfo);
            }

            AddBinding(std::move(bind));
        }
        bindings.close();
    }

    void EventManager::SetFocus(const bool& l_focus)
    {
        m_hasFocus = l_focus;
    }

    void EventManager::add_action(StateType l_state, std::string_view l_name, std::unique_ptr<ActionFunctinoid>&& l_action)
    {
        auto iter = m_actions.emplace(l_state,ActionContainer()).first;
        iter->second.emplace(l_name, std::move(l_action));
        
        // m_actions.emplace(l_name,std::move(l_action));
    }

    bool EventManager::remove_action(StateType l_state, std::string_view l_name)
    {
        auto state_itr = m_actions.find(l_state);

        if (state_itr == m_actions.end())
        {
            return false;
        }

        auto action_itr = state_itr->second.find(std::string(l_name));

        if (action_itr == state_itr->second.end())
        {
            return false;
        }
        
        state_itr->second.erase(std::string(l_name));

        return true;
    }
} // namespace Engine
