#include "GameEngine/Game.hpp"

#include <SFML/Graphics.hpp>

int main() {
    Game game("Until Rescue");
    // Game game(1000, 1000,"Until Rescue");
    game.run();
    return 0;
}
