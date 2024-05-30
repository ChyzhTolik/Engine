#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace Engine
{
    class InfoBox
    {
    public:
        InfoBox();
        InfoBox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
        ~InfoBox();

        void Setup(int l_visible, int l_charSize,
            int l_width, sf::Vector2f l_screenPos);
        void Add(std::string l_message);
        void Clear();
        void Render(sf::RenderWindow& l_wind);
    private:
        std::vector<std::string> m_messages;
        int m_numVisible;
        sf::RectangleShape m_backdrop;
        sf::Font m_font;
        sf::Text m_content;
    };
    
    
    
} // namespace Engine
