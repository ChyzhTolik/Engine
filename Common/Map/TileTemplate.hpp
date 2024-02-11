#pragma once

#include <SFML/Graphics.hpp>
#include "Configuration.hpp"

namespace Engine
{
    template<typename T = uint32_t>
    struct TileInfo
    {
        T type;
        bool is_deadly;
        sf::Vector2f friction;
        sf::Vector2i coords;
        sf::Vector2i size;
    };

    template<typename TyleType = uint32_t>
    class TileTemplate : public sf::Sprite
    {
        public:
        TileTemplate(const TileInfo<TyleType>& tile_info, Configuration::Textures texture_id);
        ~TileTemplate();

        TileInfo<TyleType> get_tile_info() const;

        TyleType get_type() const;
        void set_type(TyleType type);

        sf::Vector2f get_friction() const;
        void set_friction(const sf::Vector2f& friction);
        sf::Vector2i get_size() const;
        bool is_deadly() const;
    private:
        TileInfo<TyleType> m_tile_info;
    };

    template<typename TyleType>
	inline TileTemplate<TyleType>::TileTemplate(const TileInfo<TyleType>& tile_info, Configuration::Textures texture_id) : 
        sf::Sprite(Engine::Configuration::textures.get(texture_id)), m_tile_info(tile_info)
	{
        setTextureRect({m_tile_info.coords, m_tile_info.size});
	}

    template<typename TyleType>
    inline TileTemplate<TyleType>::~TileTemplate()
    {

    }

    template<typename TyleType>
    TyleType TileTemplate<TyleType>::get_type() const
    {
        return m_tile_info.type;
    }

    template<typename TyleType>
    void TileTemplate<TyleType>::set_type(TyleType type)
    {
        m_tile_info.type = type;
    }

    template<typename TyleType>
    TileInfo<TyleType> TileTemplate<TyleType>::get_tile_info() const
    {
        return m_tile_info;
    }

    template<typename TyleType>
    sf::Vector2f TileTemplate<TyleType>::get_friction() const
    {
        return m_tile_info.friction;
    }

    template<typename TyleType>
    sf::Vector2i TileTemplate<TyleType>::get_size() const
    {
        return m_tile_info.size;
    }

    template<typename TyleType>
    bool TileTemplate<TyleType>::is_deadly() const
    {
        return m_tile_info.is_deadly;
    }

    template<typename TyleType>
    void TileTemplate<TyleType>::set_friction(const sf::Vector2f& friction)
    {
        m_tile_info.friction = friction;
    }

    template<typename TyleType>
    inline bool operator==(const TileInfo<TyleType>& lhs, const TileInfo<TyleType>& rhs)
    {
        return lhs.coords == rhs.coords 
            && lhs.friction == rhs.friction
            && lhs.is_deadly == rhs.is_deadly
            && lhs.size == rhs.size
            && lhs.type == rhs.type;
    }
}