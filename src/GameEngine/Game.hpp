#ifndef GAME_HPP
#define GAME_HPP
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "SFML/Audio/Music.hpp"
#include "StateMachine.hpp"
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

struct GameData {
    StateMachine fsm;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
    sf::Music sound;
};

typedef std::shared_ptr<GameData> GameDataRef;


class Game {
    const float dt;
    sf::Clock clock;
    GameDataRef data;
public:
    Game(unsigned int width, unsigned int height, const string &title);
    Game(const string &title);
    ~Game();
    void run() const;
};



#endif //GAME_HPP
