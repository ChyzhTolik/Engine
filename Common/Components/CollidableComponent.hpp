#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace Engine
{
    enum class Origin
    {
        TopLeft,
        AbsCenter,
        MidBottom,
    };

    struct CollidableInfo
    {
        sf::FloatRect bounding_box;
        sf::Vector2f offset;
        Origin origin;
    };

    class CollidableComponent : public Component
    {
    public:
        CollidableComponent(/* args */);
        ~CollidableComponent();

        void read_in(json data) override;
        void collide_on_x();
        void collide_on_y();
        void resset_collision_flags();
        void set_size(const sf::Vector2f& size);
        void set_position(const sf::Vector2f& pos);
        void set_origin(Origin origin);

        bool get_colliding_on_x() const;
        bool get_colliding_on_y() const;
        sf::Vector2f get_offset() const;
        sf::Vector2f get_box_size() const;
        Origin get_origin() const;
        sf::Vector2f get_position() const;
        sf::FloatRect get_bounding_box() const;

    private:
        CollidableInfo m_collidable_info;
        bool m_colliding_on_x;
        bool m_colliding_on_y;
    };   
    
    class CollidableComponentTestHelper
    {
    public:
        static json get_json(const CollidableInfo& input);
    };

    class CollidableComponentCreator : public ComponentCreator
    {
    public:
        CollidableComponentCreator();
        virtual ~CollidableComponentCreator(){};
        virtual std::shared_ptr<Component> create() override;
    };
} // namespace Engine
