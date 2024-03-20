#pragma once

#include <SFML/Graphics.hpp>
#include "Configuration.hpp"
#include "Tile.hpp"

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

    template<typename TileType = uint32_t>
    class TileTemplate : public sf::Sprite, Tile
    {
        public:
        TileTemplate(const TileInfo<TileType>& tile_info, Configuration::Textures texture_id);
        ~TileTemplate();

        TileInfo<TileType> get_tile_info() const;

        TileType get_type() const;
        void set_type(TileType type);

        sf::Vector2f get_friction() const override;
        void set_friction(const sf::Vector2f& friction) override;
        sf::Vector2i get_size() const override;
        bool is_deadly() const override;
    private:
        TileInfo<TileType> m_tile_info;
    };

    template<typename TileType>
	inline TileTemplate<TileType>::TileTemplate(const TileInfo<TileType>& tile_info, Configuration::Textures texture_id) : 
        sf::Sprite(Engine::Configuration::textures.get(texture_id)), m_tile_info(tile_info)
	{
        setTextureRect({m_tile_info.coords, m_tile_info.size});
	}

    template<typename TileType>
    inline TileTemplate<TileType>::~TileTemplate()
    {

    }

    template<typename TileType>
    TileType TileTemplate<TileType>::get_type() const
    {
        return m_tile_info.type;
    }

    template<typename TileType>
    void TileTemplate<TileType>::set_type(TileType type)
    {
        m_tile_info.type = type;
    }

    template<typename TileType>
    TileInfo<TileType> TileTemplate<TileType>::get_tile_info() const
    {
        return m_tile_info;
    }

    template<typename TileType>
    sf::Vector2f TileTemplate<TileType>::get_friction() const
    {
        return m_tile_info.friction;
    }

    template<typename TileType>
    sf::Vector2i TileTemplate<TileType>::get_size() const
    {
        return m_tile_info.size;
    }

    template<typename TileType>
    bool TileTemplate<TileType>::is_deadly() const
    {
        return m_tile_info.is_deadly;
    }

    template<typename TileType>
    void TileTemplate<TileType>::set_friction(const sf::Vector2f& friction)
    {
        m_tile_info.friction = friction;
    }

    template<typename TileType>
    inline bool operator==(const TileInfo<TileType>& lhs, const TileInfo<TileType>& rhs)
    {
        return lhs.coords == rhs.coords 
            && lhs.friction == rhs.friction
            && lhs.is_deadly == rhs.is_deadly
            && lhs.size == rhs.size
            && lhs.type == rhs.type;
    }
}