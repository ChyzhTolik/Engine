#pragma once
#include "Anim_Base.hpp"

namespace Engine
{
    class Anim_Directional : public Anim_Base
    {
    public:
        Anim_Directional(SpriteSheet& l_sprite_sheet) : Anim_Base(l_sprite_sheet)
        {
            
        }
    protected:
        void FrameStep();
        void CropSprite();
    private:
        sf::IntRect invert_horizontal(const sf::IntRect& rect);
    };
    
} // namespace Engine
