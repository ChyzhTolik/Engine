#pragma once

namespace Engine
{
    struct EventDetails
    {
        EventDetails(const std::string& l_bindName)
            : m_name(l_bindName)
        {
            Clear();
        }

        std::string m_name;
        sf::Vector2i m_size;
        std::uint32_t m_textEntered;
        sf::Vector2i m_mouse;
        int m_mouseWheelDelta;
        int m_keyCode; // Single key code.
        void Clear()
        {
            m_size = sf::Vector2i(0, 0);
            m_textEntered = 0;
            m_mouse = sf::Vector2i(0, 0);
            m_mouseWheelDelta = 0;
            m_keyCode = -1;
        }
    };
}