#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "StateMachine.hpp"
using std::string;

struct GameData {
    StateMachine fsm;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;


class Game {
    const float dt;
    sf::Clock clock;
    GameDataRef data;
public:
    Game(unsigned int width, unsigned int height, const string &title);
    Game(const string &title);

private:
    void run();

};



#endif //GAME_HPP
