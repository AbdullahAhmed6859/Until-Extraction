#ifndef SPLASHSCREENSTATE_HPP
#define SPLASHSCREENSTATE_HPP
#include "../GameEngine/Game.hpp"
#include "../GameEngine/State.hpp"

class SplashScreenState final : public State{
    GameDataRef data;
    sf::Clock clock;
    sf::Sprite background;
    sf::Vector2f scale;
    sf::Vector2f scaleSpeed;
public:
    SplashScreenState(GameDataRef data);
    void init();
    void handleInput();
    void update(float dt);
    void render(float dt);
};

#endif //SPLASHSCREENSTATE_HPP
