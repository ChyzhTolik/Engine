#pragma once

#include <queue>

#include "IMainWindow.hpp"
#include "TestPlayer.hpp"
// #include "Heap.h"
// #include "Stats.h"
// #include "ActionTarget.h"

namespace Engine
{
    class MainWindow :
        public IMainWindow
    {
    public:

        MainWindow(const MainWindow&) = delete;
        MainWindow& operator = (const MainWindow&) = delete;
        MainWindow();
        ~MainWindow();

        // Inherited via IMainWindow
        virtual void run(int minimum_frames_per_second) override;

    private:
        virtual void process_events() override;
        virtual void update(sf::Time delta_time) override;
        virtual void render() override;

        std::unique_ptr<sf::RenderWindow> m_window;

        bool m_is_game_over = false;
        bool m_is_paused = false;
        bool m_pause_key_state = true;
        
        uint16_t m_width{ 320u }, m_heigth{ 480u };

        sf::Sprite m_back;

        std::unique_ptr<TestPlayer> m_player;
    };
}
