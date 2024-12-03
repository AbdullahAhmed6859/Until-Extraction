//
// Created by Abdullah Ahmed on 12/3/2024.
//

#include "GameState.hpp"

using namespace std;



GameState::GameState(GameDataRef data) : data(std::move(data)), map(sf::Vector2f(1280, 720)) {
}

void GameState::init() {
    map.initialize();
}

void GameState::handleInput() {
    sf::Event event{};
    while (data->window.pollEvent(event)) {
        if (InputManager::isClosedEvent(event) || InputManager::isEscPressed()) {
            data->window.close();
        }
    }
    if (InputManager::isEnterPressed()) {
        std::cout << "go to Game" << std::endl;
        data->sound.stop();
        // data->fsm.addState(StateRef(new GameState(data)), true);
    }
}

void GameState::update(const float dt) {
    map.updateHeroAndCamera(dt);
}

void GameState::render(float dt) {
    data->window.clear(sf::Color::Black);
    map.draw(data->window);
    data->window.display();
}
