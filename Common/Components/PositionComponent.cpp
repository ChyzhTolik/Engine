#include "PositionComponent.hpp"

namespace Engine
{
    PositionComponent::PositionComponent() : Component(ComponentType::Position)
    {
    }
    
    PositionComponent::~PositionComponent()
    {
    }

    void to_json(json& j, const PositionInfo& p) 
    {
        j=json{
            {"position", {p.position.x,p.position.y}},
            {"elevation", p.elevation}
        };
    }

    void from_json(const json& j, PositionInfo& p) 
    {
        float float_array[2];
        j.at("position").get_to(float_array);
        p.position = sf::Vector2f(float_array[0],float_array[1]);

        j.at("elevation").get_to(p.elevation);
    }

    void PositionComponent::read_in(json data)
    {
        m_position_info = data;
    }

    json PosComponentTestHelper::get_json(const PositionInfo& input)
    {
        json result;
        result = input;
        return result;
    }

    void PositionComponent::set_position(const sf::Vector2f& position)
    {
        m_old_position = m_position_info.position;
        m_position_info.position = position;
    }

    void PositionComponent::set_elevation(const uint32_t elevation)
    {
        m_position_info.elevation = elevation;
    }

    void PositionComponent::move_by(const sf::Vector2f& vec)
    {
        m_old_position = m_position_info.position;
        m_position_info.position += vec;
    }

    sf::Vector2f PositionComponent::get_position() const
    {
        return m_position_info.position;
    }

    sf::Vector2f PositionComponent::get_old_position() const
    {
        return m_old_position;
    }

    uint32_t PositionComponent::get_elevation() const
    {
        return m_position_info.elevation;
    }

    PositionComponentCreator::PositionComponentCreator()
    {

    }

    std::shared_ptr<Component> PositionComponentCreator::create()
    {
        return std::make_shared<PositionComponent>();
    }

} // namespace Engine