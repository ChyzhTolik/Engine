#pragma once

#include "DrawableComponentInterface.hpp"
#include "SpriteSheetTemplate.hpp"
#include "Anim_Directional.hpp"
#include "AnimationTypes.hpp"

namespace Engine
{
    struct SpriteSheetInfo
    {
        std::string file_name;
    };

    template<typename T>
    class SpriteSheetComponent : public DrawableComponentInterface
    {
    public:
        SpriteSheetComponent();
        virtual ~SpriteSheetComponent(){}

        std::shared_ptr<SpriteSheet> get_sprite_sheet() override;

        template<class Animation>
        void create(Configuration::Textures id, const std::string& file_name = "");
        
        void update_position(const sf::Vector2f& l_vec) override;
        const sf::Vector2i get_size() override;
        void draw(sf::RenderWindow& l_wind) override;
        void read_in(json data) override;
        void update(float time) override;
    private:
        std::shared_ptr<SpriteSheetTemplate<T>> m_sprite_sheet;
        SpriteSheetInfo m_sprite_sheet_info;
    };

    class SpriteSheetComponentTestHelper
    {
    public:
        static json get_json(const SpriteSheetInfo& input);
        static SpriteSheetInfo get_from_json(const json& j);
    };

    template<typename T>
    class SpriteSheetComponentCreator : public ComponentCreator
    {
    public:
        SpriteSheetComponentCreator();
        virtual ~SpriteSheetComponentCreator(){};

        virtual std::unique_ptr<Component> create() override;
    };
    
    #include "SpriteSheetComponent.tpp"
} // namespace Engine
