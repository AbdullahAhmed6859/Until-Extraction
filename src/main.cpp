#include "GameEngine/Game.hpp"

#include <SFML/Graphics.hpp>

int main() {
    // Game game("Until Rescue");
    Game game(1280, 720,"Until Rescue");
    game.run();
    return 0;
}
