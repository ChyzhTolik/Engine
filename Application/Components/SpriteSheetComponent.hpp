#pragma once

#include "DrawableComponent.hpp"
#include "SpriteSheet.hpp"

namespace Engine
{
    class SpriteSheetComponent : public DrawableComponent
    {
    public:
        SpriteSheetComponent();
        ~SpriteSheetComponent();
        void load(std::stringstream& l_stream) override;
        void Create(const std::string& l_name, int texture_id);
        std::shared_ptr<SpriteSheet> GetSpriteSheet();
        void UpdatePosition(const sf::Vector2f& l_vec) override;
        const sf::Vector2i GetSize() override;
        void Draw(sf::RenderWindow& l_wind) override;
    private:
        std::shared_ptr<SpriteSheet> m_sprite_sheet;
        std::string m_sheet_name;
    };
    
} // namespace Engine
