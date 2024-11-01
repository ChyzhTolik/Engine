#pragma once

#include "EntityManager.hpp"
#include "SpriteSheetTemplate.hpp"
#include <AnimationTypes.hpp>

namespace Engine
{
    struct CharInfo
    {
        std::string Name;
        int Spritesheet;
        std::string Animations;
        uint32_t Hitpoints;
        sf::Vector2u BoundingBox;
        sf::FloatRect DamageBox;
        sf::Vector2f Speed;
        float JumpVelocity;
        sf::Vector2f MaxVelocity;
    };

    class Character : public EntityBase
    {
        friend class EntityManager;
    public:
        Character(EntityManager& l_entityMgr);
        virtual ~Character();
        void Move(const Direction& l_dir);
        void Jump();
        void Attack();
        void GetHurt(const int& l_damage);
        void Load(const std::string& l_path);
        virtual void OnEntityCollision(EntityBase& l_collider, bool l_attack) = 0;
        virtual void Update(float l_dT);
        void Draw(sf::RenderWindow& l_wind);
        SpriteSheetTemplate<KnightAnimations>& get_sprite_steet();

    protected:
        virtual void UpdateAABB(Direction direction) override;
        void UpdateAttackAABB();
        void Animate();
        SpriteSheetTemplate<KnightAnimations> m_spriteSheet;
        float m_jumpVelocity;
        int m_hitpoints;
        sf::FloatRect m_attackAABB;
        sf::Vector2f m_attackAABBoffset;
    };
} // namespace Engine
