#pragma once
#include <unordered_map>
#include <exception>
#include <memory>

#include <SFML/Audio.hpp>

namespace Engine
{
	template <typename RESOURCE, typename IDENTIFIER = int>
	class ResourceManager
	{
	public:
		using ResourcePtr = std::unique_ptr<RESOURCE>;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator = (const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		void load(const IDENTIFIER& id, Args&& ... args);
		void clear();

		RESOURCE& get(const IDENTIFIER& id) const;

	private:
		std::unordered_map<IDENTIFIER, ResourcePtr> m_map;
	};

	template<typename RESOURCE, typename IDENTIFIER>
	template<typename ...Args>
	inline void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args && ...args)
	{
		ResourcePtr res = std::make_unique<RESOURCE>();

		if (!res->loadFromFile(std::forward<Args>(args) ...))
		{
			throw std::runtime_error("Impossible to load file");
		}

		m_map.emplace(id, std::move(res));
	}

	template<typename RESOURCE, typename IDENTIFIER>
	inline void ResourceManager<RESOURCE, IDENTIFIER>::clear()
	{
		m_map.clear();
	}

	template<typename RESOURCE, typename IDENTIFIER>
	inline RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id) const
	{
		return *m_map.at(id);
	}

	template<typename IDENTIFIER>
	class ResourceManager<sf::Music, IDENTIFIER>
	{
	public:
		using MusicPtr = std::unique_ptr<sf::Music>;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		void load(const IDENTIFIER& id, Args&& ... args);

		sf::Music& get(const IDENTIFIER& id) const;

	private:
		std::unordered_map<IDENTIFIER, MusicPtr> m_map;
	};

	template<typename IDENTIFIER>
	template<typename ... Args>
	void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
	{
		MusicPtr music = std::make_unique<sf::Music>();

		if (not music->openFromFile(std::forward<Args>(args)...))
		{
			throw std::runtime_error("Impossible to load file");
		}

		m_map.emplace(id, std::move(music));
	};

	template<typename IDENTIFIER>
	inline sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
	{
		return *m_map.at(id);
	}
}
