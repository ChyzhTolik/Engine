#pragma once

#include <SFML/System.hpp>

#include "Component.hpp"

namespace Engine
{
    class PositionComp : public Component
    {
    public:
        PositionComp();
        ~PositionComp();
        void load(std::stringstream& l_stream) override;
        void set_position(sf::Vector2f position);
        void set_elevation(uint32_t elevation);
        sf::Vector2f get_position_old() const;
        sf::Vector2f get_position() const;
        uint32_t get_elevation() const;
        void MoveBy(sf::Vector2f shift);

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_positionOld;
        uint32_t m_elevation;
    };    
} // namespace Engine