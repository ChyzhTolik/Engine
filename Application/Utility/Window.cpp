#include "Window.hpp"

namespace Engine
{
    Window::Window()
    {
        Setup("Window", {600,800});
    }
    
    Window::Window(std::string_view l_title,const sf::Vector2u& l_size)
    {
        Setup(l_title, l_size);
    }

    Window::~Window()
    {
        Destroy();
    }

    void Window::Setup(std::string_view l_title, const sf::Vector2u& l_size)
    {
        m_windowTitle = l_title;
        m_windowSize = l_size;
        m_isFullscreen = false;
        m_isDone = false;
        Create();
    }

    void Window::Create()
    {
        auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        m_window.create(sf::VideoMode(m_windowSize,32),m_windowTitle,style);
    }

    void Window::Destroy()
    {
        m_window.close();
    }

    void Window::BeginDraw()
    {

    }

    void Window::EndDraw()
    {

    }

    void Window::Update()
    {
        sf::Event event;

        while(m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_isDone = true;
            } 
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            {
                ToggleFullscreen();
            }
        }
    }
    bool Window::IsDone()
    {

    }

    bool Window::IsFullscreen()
    {

    }

    sf::Vector2u Window::GetWindowSize()
    {

    }

    void Window::ToggleFullscreen()
    {

    }

    void Window::Draw(sf::Drawable& l_drawable)
    {

    }
} // namespace Engine
