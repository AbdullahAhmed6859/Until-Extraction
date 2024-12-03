//
// Created by Abdullah Ahmed on 12/3/2024.
//

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include "../GameEngine/Game.hpp"
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

class GameState : public State{
    GameDataRef data;
    sf::Clock clock;
    sf::Sprite background;
    TileMap map;
public:
    GameState(GameDataRef data);
    void init();
    void handleInput();
    void update(float dt);
    void render(float dt);
};



#endif //GAMESTATE_HPP
