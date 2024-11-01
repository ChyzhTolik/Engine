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
        m_eventManager = std::make_shared<EventManager>();
        m_windowTitle = l_title;
        m_windowSize = l_size;
        m_isFullscreen = false;
        m_isDone = false;
        m_isFocused = true;
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

    void Window::BeginDraw(sf::Color color)
    {
        m_window.clear(color);
    }

    void Window::EndDraw()
    {
        m_window.display();
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
            else if (event.type == sf::Event::LostFocus)
            {
                m_isFocused = false;
                m_eventManager->SetFocus(false);
            }
            else if (event.type == sf::Event::GainedFocus)
            {
                m_isFocused = true;
                m_eventManager->SetFocus((true));
            }

            m_eventManager->HandleEvent(event);
        }

        m_eventManager->Update();
    }
    bool Window::IsDone()
    {
        return m_isDone;
    }

    bool Window::IsFullscreen()
    {
        return m_isFullscreen;
    }

    sf::Vector2u Window::GetWindowSize()
    {
        return m_windowSize;
    }

    void Window::ToggleFullscreen()
    {
        m_isFullscreen = !m_isFullscreen;
        Destroy();
        Create();
    }

    void Window::Draw(sf::Drawable& l_drawable)
    {
        m_window.draw(l_drawable);
    }

    void Window::Close(EventDetails& l_details)
    {
        m_isDone = true;
    }

    void Window::ToggleFullscreen(EventDetails& l_details)
    {
        m_isFullscreen = !m_isFullscreen;
        m_window.close();
        Create();
    }

    std::shared_ptr<EventManager> Window::GetEventManager()
    {
        return m_eventManager;
    }

    sf::RenderWindow& Window::GetRenderWindow()
    {
        return m_window;
    }

    sf::FloatRect Window::GetViewSpace()
    {
        sf::Vector2f viewCenter = m_window.getView().getCenter();
        sf::Vector2f viewSize = m_window.getView().getSize();
        sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
        sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
        
        return viewSpace;
    }
} // namespace Engine
