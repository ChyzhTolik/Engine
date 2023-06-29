#include "State_Intro.hpp"
#include "StateManager.hpp"

namespace Engine
{
    void State_Intro::OnCreate(const sf::Texture& l_texture)
    {
        m_timePassed = 0.0f;
        sf::Vector2u windowSize = m_stateMgr.GetContext().m_wind.GetRenderWindow().getSize();
        m_introTexture.loadFromFile("intro.png");
        m_introSprite.setTexture(m_introTexture);
    }
} // namespace Engine
