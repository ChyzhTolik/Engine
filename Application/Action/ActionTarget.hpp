#pragma once
#include <functional>
#include <list>
#include <SFML/Graphics.hpp>
#include "Action.hpp"
#include "ActionMap.hpp"

namespace Engine
{
	template<typename T = int>
	class ActionTarget
	{
	public:
		ActionTarget(const ActionTarget<T>&) = delete;
		ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;
		using FuncType = std::function<void(const sf::Event&)>;

		ActionTarget(const ActionMap<T>& map);

		bool process_event(const sf::Event& event) const;
		void process_events() const;

		void bind(const T& key, const FuncType& callback);
		void unbind(const T& key);

	private:
		std::list<std::pair<Action, FuncType>> m_events_real_time;
		std::list<std::pair<Action, FuncType>> m_events_poll;

		const ActionMap<T>& m_action_map;
	};

	template<typename T>
	inline ActionTarget<T>::ActionTarget(const ActionMap<T>& map) : m_action_map(map)
	{
	}

	template<typename T>
	inline bool ActionTarget<T>::process_event(const sf::Event& event) const
	{
		bool result = false;

		for (auto& action : m_events_poll)
		{
			if (action.first == event)
			{
				action.second(event);
				result = true;
				break;
			}
		}

		return result;
	}

	template<typename T>
	inline void ActionTarget<T>::process_events() const
	{
		for (auto& action : m_events_real_time)
		{
			if (action.first.test())
			{
				action.second(action.first.m_event);
			}
		}
	}

	template<typename T>
	inline void ActionTarget<T>::bind(const T& key, const FuncType& callback)
	{
		const Action& action = m_action_map.get(key);

		if (action.m_type & Action::to_int(Action::Type::RealTime))
		{
			m_events_real_time.emplace_back(action, callback);
		}
		else
		{
			m_events_poll.emplace_back(action, callback);
		}
	}

	template<typename T>
	inline void ActionTarget<T>::unbind(const T& key)
	{
		auto remove_func = [&key](const std::pair<T, FuncType>& pair)->bool
		{
			return pair.first == key;
		};

		const Action& action = m_action_map.get(key);
		if (action.m_type & Action::to_int(Action::Type::RealTime))
		{
			m_events_real_time.remove_if(remove_func);
		}
		else
		{
			m_events_poll.remove_if(remove_func);
		}
	}
}

