#pragma once

#include "Component.hpp"
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
    class SpriteSheetComponent : public Component
    {
    public:
        SpriteSheetComponent();
        virtual ~SpriteSheetComponent(){}

        auto get_sprite_sheet();

        template<class Animation>
        void create(Configuration::Textures id, const std::string& file_name = "");
        
        void update_position(const sf::Vector2f& l_vec);
        const sf::Vector2i& get_size();
        void draw(sf::RenderWindow& l_wind);
        void read_in(json data) override;
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

        virtual std::shared_ptr<Component> create() override;
    };
    
    #include "SpriteSheetComponent.tpp"
} // namespace Engine
