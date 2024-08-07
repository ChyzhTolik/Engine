#include "CollidableComponent.hpp"

namespace Engine
{
    CollidableComponent::CollidableComponent(/* args */) : Component(ComponentType::Collidable), m_colliding_on_x{false},
        m_colliding_on_y{false}, m_collidable_info{}
    {
    }
    
    CollidableComponent::~CollidableComponent()
    {
    }

    void to_json(json& j, const CollidableInfo& p) 
    {
        j=json{
            {"bounding_box", {p.bounding_box.width,p.bounding_box.height}},
            {"offset", {p.offset.x,p.offset.y}},
            {"origin", p.origin}
        };
    }

    void from_json(const json& j, CollidableInfo& p) 
    {
        float float_array[2];
        j.at("bounding_box").get_to(float_array);
        p.bounding_box = sf::FloatRect({},{float_array[0],float_array[1]});

        j.at("offset").get_to(float_array);
        p.offset = sf::Vector2f(float_array[0],float_array[1]);

        j.at("origin").get_to(p.origin);
    }

    void CollidableComponent::read_in(json data)
    {
        m_collidable_info = data;
    }

    json CollidableComponentTestHelper::get_json(const CollidableInfo& input)
    {
        json result;
        result = input;
        return result;
    }

    void CollidableComponent::collide_on_x()
    {
        m_colliding_on_x = true;
    }

    void CollidableComponent::collide_on_y()
    {
        m_colliding_on_y = true;
    }

    void CollidableComponent::resset_collision_flags()
    {
        m_colliding_on_x = false;
        m_colliding_on_y = false;
    }

    void CollidableComponent::set_size(const sf::Vector2f& size)
    {
        m_collidable_info.bounding_box.width = size.x;
        m_collidable_info.bounding_box.height = size.y;
    }

    void CollidableComponent::set_position(const sf::Vector2f& pos)
    {
        switch (m_collidable_info.origin)
        {
        case Origin::TopLeft:
            m_collidable_info.bounding_box.left = pos.x + m_collidable_info.offset.x;
            m_collidable_info.bounding_box.top = pos.y + m_collidable_info.offset.y;
            break;

        case Origin::AbsCenter:
            m_collidable_info.bounding_box.left = pos.x - m_collidable_info.bounding_box.width/2 + m_collidable_info.offset.x;
            m_collidable_info.bounding_box.top = pos.y - m_collidable_info.bounding_box.height/2 + m_collidable_info.offset.y;
            break;
        
        case Origin::MidBottom:
            m_collidable_info.bounding_box.left = pos.x - m_collidable_info.bounding_box.width/2 + m_collidable_info.offset.x;
            m_collidable_info.bounding_box.top = pos.y - m_collidable_info.bounding_box.height + m_collidable_info.offset.y;
            break;

        default:
            break;
        }
    }

    CollidableComponentCreator::CollidableComponentCreator()
    {

    }

    std::unique_ptr<Component> CollidableComponentCreator::create()
    {
        return std::make_unique<CollidableComponent>();
    }

    bool CollidableComponent::get_colliding_on_x() const
    {
        return m_colliding_on_x;
    }

    bool CollidableComponent::get_colliding_on_y() const
    {
        return m_colliding_on_y;
    }

    sf::Vector2f CollidableComponent::get_offset() const
    {
        return m_collidable_info.offset;
    }

    sf::Vector2f CollidableComponent::get_box_size() const
    {
        return sf::Vector2f(m_collidable_info.bounding_box.width, m_collidable_info.bounding_box.height);
    }

    Origin CollidableComponent::get_origin() const
    {
        return m_collidable_info.origin;
    }

    void CollidableComponent::set_origin(Origin origin)
    {
        m_collidable_info.origin = origin;
    }

    sf::Vector2f CollidableComponent::get_position() const
    {
        return {m_collidable_info.bounding_box.left,m_collidable_info.bounding_box.top};
    }

    sf::FloatRect CollidableComponent::get_bounding_box() const
    {
        return m_collidable_info.bounding_box;
    }

    void CollidableComponent::set_offset(const sf::Vector2f& offset)
    {
        m_collidable_info.offset = offset;
    }
} // namespace Engine
