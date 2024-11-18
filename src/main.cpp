#include "GameEngine/Game.hpp"

#include <SFML/Graphics.hpp>

int main() {
    // auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    // window.setFramerateLimit(144);
    //
    // while (window.isOpen()) {
    //     for (auto event = sf::Event(); window.pollEvent(event);) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }
    //     window.clear();
    //     window.display();
    // }
    Game game("Until Rescue");
    // Game game(1000, 1000,"Until Rescue");
    return 0;
}
