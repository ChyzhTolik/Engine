#pragma once

#include <SFML/Graphics.hpp>
#include "IPlayable.hpp"
#include <ActionTarget.hpp>
#include <Configuration.hpp>

namespace Engine
{
    class TestPlayer : public IPlayable, public sf::Drawable, public ActionTarget<Configuration::TetrisInputs>
    {
    private:
        sf::CircleShape m_circle;
    public:
        TestPlayer();
        ~TestPlayer();
        void virtual update(sf::Time delta_time) override;
		void virtual process_events() override;
    private:
        virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    };    
} // namespace Engine
