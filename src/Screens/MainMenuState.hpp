//
// Created by Abdullah Ahmed on 11/19/2024.
//

#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP
#include "../GameEngine/Game.hpp"
#include "../GameEngine/State.hpp"

class MainMenuState final : public State{
    GameDataRef data;
    sf::Clock clock;
    sf::Sprite background;
public:
    MainMenuState(GameDataRef data);
    void init();
    void handleInput();
    void update(float dt);
    void render(float dt);
};


#endif //MAINMENUSTATE_HPP
