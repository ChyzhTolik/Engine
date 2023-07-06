#pragma once
#include "Anim_Base.hpp"

namespace Engine
{
    class Anim_Directional : public Anim_Base
    {
    protected:
        void FrameStep();
        void CropSprite();
    private:
        sf::IntRect invert_horizontal(const sf::IntRect& rect);
    };
    
} // namespace Engine
