#include "StateManager.hpp"
#include "State_Intro.hpp"
#include "State_MainMenu.hpp"
#include "State_Game.hpp"
#include "State_Paused.hpp"

namespace Engine
{
	StateManager::StateManager(SharedContext& l_shared) : m_shared(l_shared)
	{
		RegisterState<State_Intro>(StateType::Intro);
		RegisterState<State_MainMenu>(StateType::MainMenu);
		RegisterState<State_Game>(StateType::Game);
		RegisterState<State_Paused>(StateType::Paused);
	}

	StateManager::~StateManager()
	{
		for (auto& state : m_states)
		{
			state.second->OnDestroy();
		}
	}

	void StateManager::Draw()
	{
		if (m_states.empty())
		{
			return;
		}

		if (m_states.back().second->IsTransparent() && m_states.size() > 1)
		{
			auto itr = m_states.end();

			while (itr != m_states.begin())
			{
				if (itr != m_states.end())
				{
					if (!itr->second->IsTransparent())
					{
						break;
					}
				}

				--itr;
			}

			for (; itr != m_states.end(); ++itr)
			{
				itr->second->Draw();
			}
		}
		else
		{
			m_states.back().second->Draw();
		}
	}

	void StateManager::Update(const sf::Time& l_time)
	{
		if (m_states.empty())
		{
			return;
		}

		if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
		{
			auto itr = m_states.end();

			while (itr != m_states.begin())
			{
				if (itr != m_states.end())
				{
					if (!itr->second->IsTranscendent())
					{
						break;
					}
				}

				--itr;
			}

			for (; itr != m_states.end(); ++itr)
			{
				itr->second->Update(l_time);
			}
		}
		else
		{
			m_states.back().second->Update(l_time);
		}
	}

	SharedContext& StateManager::GetContext()
	{
		return m_shared;
	}

	bool StateManager::HasState(const StateType& l_type)
	{
		for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
		{
			if (itr->first == l_type)
			{
				auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);

				if (removed == m_toRemove.end())
				{
					return true;
				}

				return false;
			}
		}

		return false;
	}

	void StateManager::Remove(const StateType& l_type)
	{
		m_toRemove.erase(m_toRemove.begin());
	}

	void StateManager::ProcessRequests()
	{
		while (m_toRemove.begin() != m_toRemove.end())
		{
			RemoveState(*m_toRemove.begin());
			m_toRemove.erase(m_toRemove.begin());
		}
	}

	void StateManager::SwitchTo(const StateType& l_type)
	{
		m_shared.m_eventManager.SetCurrentState(l_type);

		for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
		{
			if (itr->first == l_type)
			{
				m_states.back().second->Deactivate();

				StateType tmp_type = itr->first;
				auto tmp_state = std::move(itr->second);
				m_states.erase(itr);
				m_states.emplace_back(tmp_type, std::move(tmp_state));
				tmp_state->Activate();
				return;
			}

			// State with l_type wasn't found.
			if (!m_states.empty())
			{
				m_states.back().second->Deactivate();
			}

			CreateState(l_type);
			m_states.back().second->Activate();
		}
	}

	void StateManager::CreateState(const StateType& l_type)
	{
		auto newState = m_stateFactory.find(l_type);

		if (newState == m_stateFactory.end())
		{
			return;
		}

		auto state = newState->second();
		m_states.emplace_back(l_type, state);
        sf::Texture test_texture;
		state->OnCreate(test_texture);
	}

	void StateManager::RemoveState(const StateType& l_type)
	{
		for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
		{
			if (itr->first == l_type) 
			{
				itr->second->OnDestroy();
				m_states.erase(itr);
				return;
			}
		}
	}
} // namespace Engine