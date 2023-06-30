#pragma once
#include <unordered_map>
#include <exception>

#include <SFML/Audio.hpp>

namespace Engine
{
	template <typename RESOURCE, typename IDENTIFIER = int>
	class ResourceManager
	{
	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator = (const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		void load(const IDENTIFIER& id, Args&& ... args);
		void clear();

		const RESOURCE& get(const IDENTIFIER& id) const;

	private:
		std::unordered_map<IDENTIFIER, RESOURCE> m_map;
	};

	template<typename RESOURCE, typename IDENTIFIER>
	template<typename ...Args>
	inline void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args && ...args)
	{
		RESOURCE res;

		if (!res.loadFromFile(std::forward<Args>(args) ...))
		{
			throw std::runtime_error("Impossible to load file");
		}

		m_map.insert({id, res});
	}

	template<typename RESOURCE, typename IDENTIFIER>
	inline void ResourceManager<RESOURCE, IDENTIFIER>::clear()
	{
		m_map.clear();
	}

	template<typename RESOURCE, typename IDENTIFIER>
	inline const RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id) const
	{
		return m_map.at(id);
	}

	template<typename IDENTIFIER>
	class ResourceManager<sf::Music, IDENTIFIER>
	{
	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		void load(const IDENTIFIER& id, Args&& ... args);

		const sf::Music& get(const IDENTIFIER& id) const;

	private:
		std::unordered_map<IDENTIFIER, sf::Music> m_map;
	};

	template<typename IDENTIFIER>
	template<typename ... Args>
	void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
	{
		sf::Music music;

		if (not music.openFromFile(std::forward<Args>(args)...))
		{
			throw std::runtime_error("Impossible to load file");
		}

		m_map.insert(id, music);
	};

	template<typename IDENTIFIER>
	const sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
	{
		return m_map.at(id);
	}
}
