#include "SpriteSheetComponent.hpp"

namespace Engine
{
    SpriteSheetComponent::SpriteSheetComponent() : DrawableComponent(ComponentType::SpriteSheet), m_sprite_sheet(nullptr)
    {
    }
    
    SpriteSheetComponent::~SpriteSheetComponent()
    {
    }

    void SpriteSheetComponent::load(std::stringstream& l_stream)
    {
        l_stream>>m_sheet_name;
    }

    void SpriteSheetComponent::Create(const std::string& l_name, int texture_id)
    {
        if (m_sprite_sheet)
        { 
            return; 
        }

        m_sprite_sheet = std::make_shared<SpriteSheet>();
        m_sprite_sheet->LoadSheet("media/Json/" +(l_name != "" ? l_name : m_sheet_name) + ".json", texture_id);
    }

    std::shared_ptr<SpriteSheet> SpriteSheetComponent::GetSpriteSheet()
    { 
        return m_sprite_sheet; 
    }

    void SpriteSheetComponent::UpdatePosition(const sf::Vector2f& l_vec)
    {
        m_sprite_sheet->SetSpritePosition(l_vec);
    }

    const sf::Vector2i SpriteSheetComponent::GetSize()
    {
        if (!m_sprite_sheet)
        { 
            return sf::Vector2i(0,0); 
        }

        return m_sprite_sheet->GetSpriteSize();
    }

    void SpriteSheetComponent::Draw(sf::RenderWindow& l_wind)
    {
        if (!m_sprite_sheet)
        { 
            return; 
        }

        m_sprite_sheet->Draw(l_wind);
    }

} // namespace Engine
