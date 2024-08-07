#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace Engine
{
    struct PositionInfo
    {
        sf::Vector2f position;
        uint32_t elevation;
    };

    class PositionComponent : public Component
    {    
    public:
        PositionComponent();
        ~PositionComponent();

        void read_in(json data) override;
        void set_position(const sf::Vector2f& position);
        void set_elevation(const uint32_t elevation);
        void move_by(const sf::Vector2f& vec);

        sf::Vector2f get_position() const;
        sf::Vector2f get_old_position() const;
        uint32_t get_elevation() const;

    private:
        PositionInfo m_position_info;
        sf::Vector2f m_old_position;
    };

    class PosComponentTestHelper
    {
    public:
        static json get_json(const PositionInfo& input);
    };

    class PositionComponentCreator : public ComponentCreator
    {
    public:
        PositionComponentCreator();
        virtual ~PositionComponentCreator(){};
        virtual std::unique_ptr<Component> create() override;
    };
    
} // namespace Engine
