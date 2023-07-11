#pragma once

#include <SFML/Graphics.hpp>
#include <string_view>
#include "EventManager.hpp"
#include <memory>

namespace Engine
{
    class Window
    {
    public:
        Window();
        Window(std::string_view l_title,const sf::Vector2u& l_size);
        ~Window();
        void BeginDraw(); // Clear the window.
        void EndDraw(); // Display the changes.
        void Update();
        bool IsDone();
        bool IsFullscreen();
        sf::Vector2u GetWindowSize();
        void ToggleFullscreen();
        void Draw(sf::Drawable& l_drawable);
        bool IsFocused();
        std::shared_ptr<EventManager> GetEventManager();
        void ToggleFullscreen(EventDetails& l_details);
        void Close(EventDetails& l_details);
        sf::RenderWindow& GetRenderWindow();
        sf::FloatRect GetViewSpace();

    private:
        void Setup(std::string_view l_title, const sf::Vector2u& l_size);
        void Destroy();
        void Create();
        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        std::string m_windowTitle;
        bool m_isDone;
        bool m_isFullscreen;
        std::shared_ptr<EventManager> m_eventManager;
        bool m_isFocused;
    };    
} // namespace Engine
