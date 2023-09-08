#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace Engine
{
    enum class Origin{ Top_Left, Abs_Centre, Mid_Bottom };

    class CollisionComponent : public Component
    {
    public:
        CollisionComponent(/* args */);
        ~CollisionComponent();
        void load(std::stringstream& l_stream);
        void CollideOnX();
        void CollideOnY();
        void ResetCollisionFlags();
        void SetSize(const sf::Vector2f& l_vec);
        void SetPosition(const sf::Vector2f& l_vec);
        const sf::FloatRect& GetCollidable() const;
    private:
        sf::FloatRect m_AABB;
        sf::Vector2f m_offset;
        Origin m_origin;
        bool m_collidingOnX;
        bool m_collidingOnY;
    };
} // namespace Engine
