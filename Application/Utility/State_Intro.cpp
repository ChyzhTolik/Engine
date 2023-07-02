#include "State_Intro.hpp"
#include "StateManager.hpp"

namespace Engine
{
    State_Intro::State_Intro(StateManager& l_stateManager, const sf::Texture& l_texture, const sf::Font& font) : 
        BaseState(l_stateManager), m_introSprite(l_texture), m_text(font), m_timePassed(0.0f)
    {

    }

    void State_Intro::OnCreate()
    {
        m_timePassed = 0.0f;
        sf::Vector2u windowSize = m_stateMgr.GetContext().m_wind.GetRenderWindow().getSize();
        m_introSprite.setOrigin({m_introSprite.getTexture()->getSize().x / 2.0f, m_introSprite.getTexture()->getSize().y / 2.0f});
        m_introSprite.setPosition({windowSize.x / 2.0f, 0});
        m_text.setString({ "Press SPACE to continue" });
        m_text.setCharacterSize(15);
        sf::FloatRect textRect = m_text.getLocalBounds();
        m_text.setOrigin({textRect.left + textRect.width / 2.0f,textRect.top + textRect.height / 2.0f});
        m_text.setPosition({windowSize.x / 2.0f, windowSize.y / 2.0f});
        EventManager& evMgr = m_stateMgr.GetContext().m_eventManager;
        evMgr.add_action(StateType::Intro,"Intro_Continue",std::make_unique<ContinueAction>(*this));
    }

    void State_Intro::OnDestroy()
    {
        m_stateMgr.GetContext().m_eventManager.remove_action(StateType::Intro, "Intro_Continue");
    }

    void State_Intro::Update(const sf::Time& l_time)
    {
        if(m_timePassed < 5.0f)
        { // Less than five seconds.
            m_timePassed += l_time.asSeconds();
            m_introSprite.setPosition({m_introSprite.getPosition().x, m_introSprite.getPosition().y + (48 * l_time.asSeconds())});
        }
    }

    void State_Intro::Draw()
    {
        sf::RenderWindow& window = m_stateMgr.GetContext().m_wind.GetRenderWindow();
        window.draw(m_introSprite);

        if(m_timePassed >= 5.0f)
        {
            window.draw(m_text);
        }
    }

    void State_Intro::Activate(){};
    void State_Intro::Deactivate(){};

    State_Intro::ContinueAction::ContinueAction(State_Intro& state) : m_state(state)
    {

    }

    void State_Intro::ContinueAction::execute(EventDetails& l_details)
    {
        if(m_state.m_timePassed >= 5.0f)
        {
            m_state.m_stateMgr.SwitchTo(StateType::MainMenu);
            m_state.m_stateMgr.Remove(StateType::Intro);
        }
    }

    IntroCreator::IntroCreator(StateManager& l_state_manager, const sf::Texture& l_texture, const sf::Font& l_font) : StateCreator(l_state_manager),
        m_texture(l_texture), m_font(l_font)
    {
        
    }

    std::unique_ptr<BaseState> IntroCreator::create()
    {
        return std::make_unique<State_Intro>(m_state_manager, m_texture, m_font);    
    }
} // namespace Engine
