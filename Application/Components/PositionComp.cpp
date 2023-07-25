#include "PositionComp.hpp"

namespace Engine
{
    PositionComp::PositionComp(ComponentType type) : Component(type)
    {
    }
    
    PositionComp::~PositionComp()
    {
    }

    void to_json(json& j, const sf::Vector2f& p)
    {
        j=json{
            {"x", p.x},
            {"y", p.y},
        };
    }

    void from_json(const json& j, sf::Vector2f& p)
    {
        j.at("x").get_to(p.x);
        j.at("y").get_to(p.y);
    }

    void PositionComp::load(std::stringstream& l_stream)
    {
        json pos_json = json::parse(l_stream);

        sf::Vector2f position;
        position.x = pos_json["x"];
        position.y = pos_json["y"];

        m_position = position;
    }

    void PositionComp::set_position(sf::Vector2f position)
    {
        m_position = position;
    }

    void PositionComp::set_elevation(uint32_t elevation)
    {
        m_elevation=elevation;
    }

    sf::Vector2f PositionComp::get_position() const
    {
        return m_position;
    }

    uint32_t PositionComp::get_elevation() const
    {
        return m_elevation;
    }

    sf::Vector2f PositionComp::get_position_old() const
    {
        return m_positionOld;
    }

    void PositionComp::MoveBy(sf::Vector2f shift)
    {
        m_positionOld = m_position;
        m_position += shift;
    }

} // namespace Engine
