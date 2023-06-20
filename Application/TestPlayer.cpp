#include "TestPlayer.hpp"

namespace Engine
{
    TestPlayer::TestPlayer() : ActionTarget(Configuration::tetris_inputs)
    {
        m_circle.setFillColor(sf::Color::Red);
        m_circle.setRadius(40.f);
        m_circle.setOrigin({50.f, 50.f});
    }
    
    TestPlayer::~TestPlayer()
    {
    }

    void TestPlayer::update(sf::Time delta_time)
    {

    }
	void  TestPlayer::process_events()
    {

    }
    
    void TestPlayer::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
    {
        target.draw(m_circle, states);
    }
} // namespace Engine
