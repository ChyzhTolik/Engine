#pragma once
#include <unordered_map>
#include <memory>
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

		RESOURCE& get(const IDENTIFIER& id) const;

	private:
		std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_map;
	};

	template<typename RESOURCE, typename IDENTIFIER>
	template<typename ...Args>
	inline void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args && ...args)
	{
		std::unique_ptr<RESOURCE> res_ptr = std::make_unique<RESOURCE>();

		if (!res_ptr->loadFromFile(std::forward<Args>(args) ...))
		{
			throw std::runtime_error("Impossible to load file");
		}

		m_map.emplace(id, std::move(res_ptr));
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
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		void load(const IDENTIFIER& id, Args&& ... args);

		sf::Music& get(const IDENTIFIER& id)const;

	private:
		std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> m_map;
	};

	template<typename IDENTIFIER>
	template<typename ... Args>
	void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
	{
		std::unique_ptr<sf::Music> music_ptr(new sf::Music);

		if (not music_ptr->openFromFile(std::forward<Args>(args)...))
		{
			throw std::runtime_error("Impossible to load file");
		}

		m_map.emplace(id, std::move(music_ptr));
	};

	template<typename IDENTIFIER>
	sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
	{
		return *m_map.at(id);
	}
}
