#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

#include "Animation.hpp"

namespace Engine
{
    using AnimationPtr = std::shared_ptr<Animation>;

    class AnimatedSprite : public sf::Sprite
    {
    public:
        enum class Status
        {
            Stopped,
            Paused,
            Playing
        };

    private:
        AnimationPtr m_animation;
        sf::Time m_delta;
        sf::Time m_elapsed;
        bool m_loop;
        int m_repeat;
        Status m_status;
        size_t m_current_frame;
        sf::Vertex m_vertices[4];
        void set_frame(size_t index,bool resetTime);

    public:
        ~AnimatedSprite(){};
        AnimatedSprite(const AnimatedSprite&) = default;
        AnimatedSprite& operator=(const AnimatedSprite&) = default;
        AnimatedSprite(AnimatedSprite&&) = default;
        AnimatedSprite& operator=(AnimatedSprite&&) = default;

        using FuncType = std::function<void()>;
        static FuncType defaultFunc;
        FuncType on_finished;        

        AnimatedSprite(
            AnimationPtr animation = nullptr,
            Status status=Status::Playing,
            const sf::Time& deltaTime = sf::seconds(0.15),
            bool loop = true,int repeat=0
        );

        void set_animation(AnimationPtr animation);
        AnimationPtr get_animation()const;
        void set_frame_time(sf::Time deltaTime);
        sf::Time get_frame_time()const;
        void set_loop(bool loop);
        bool get_loop()const;
        void set_repeat(int nb);
        int get_repeat()const;
        void play();
        void pause();
        void stop();
        Status get_status()const;
        void set_frame(size_t index);
        void set_color(const sf::Color& color);
        void update(const sf::Time& deltaTime);
    };    
} // namespace Engine
