#include "StateManager.hpp"
#include "States/State_Game.hpp"
#include "States/State_Paused.hpp"
#include "States/State_Intro.hpp"
#include "States/State_MainMenu.hpp"
#include "Configuration.hpp"

namespace Engine
{
	StateManager::StateManager(SharedContext& l_shared) : m_shared(l_shared)
	{
		sf::Texture& text_texture = Configuration::textures.get(Configuration::Textures::Intro);
		sf::Font& font = Configuration::fonts.get(Configuration::Fonts::Arial);
		RegisterState<GameCreator>(StateType::Game, Configuration::textures.get(Configuration::Textures::Background));
		RegisterState<PauseCreator>(StateType::Paused, Configuration::fonts.get(Configuration::Fonts::Arial));
		RegisterState<MenuCreator>(StateType::MainMenu,Configuration::fonts.get(Configuration::Fonts::Arial));
		RegisterState<IntroCreator>(StateType::Intro, 
									Configuration::textures.get(Configuration::Textures::Intro), 
									Configuration::fonts.get(Configuration::Fonts::Arial));
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
				m_shared.m_wind->GetRenderWindow().setView(itr->second->GetView());
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
		m_toRemove.push_back(l_type);
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
		m_shared.m_eventManager->SetCurrentState(l_type);

		// State with l_type was found
		for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
		{
			if (itr->first == l_type)
			{
				m_states.back().second->Deactivate();

				StateType tmp_type = itr->first;
				auto tmp_state = std::move(itr->second);
				m_states.erase(itr);
				m_states.emplace_back(tmp_type, std::move(tmp_state));
				m_states.back().second->Activate();

				m_shared.m_wind->GetRenderWindow().setView(m_states.back().second->GetView());
				return;
			}
		}

		// State with l_type wasn't found.
		if (!m_states.empty())
		{
			m_states.back().second->Deactivate();
		}

		CreateState(l_type);
		m_states.back().second->Activate();
		m_shared.m_wind->GetRenderWindow().setView(m_states.back().second->GetView());
	}

	void StateManager::CreateState(const StateType& l_type)
	{
		auto newState = m_stateFactory.find(l_type);

		if (newState == m_stateFactory.end())
		{
			return;
		}

		auto state = newState->second->create();
		state->m_view = m_shared.m_wind->GetRenderWindow().getDefaultView();

		m_states.emplace_back(l_type, std::move(state));
		m_states.back().second->OnCreate();
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

	void StateManager::set_game_callback(std::function<void()> callback)
	{
		auto it = std::find_if(m_states.begin(),m_states.end(),[](std::pair<StateType, std::unique_ptr<BaseState>>& state_pair){
			return state_pair.first == StateType::Game;
		});

		if (it!=m_states.end())
		{
			it->second->set_callback(callback);
		}
		
	}
} // namespace Engine
