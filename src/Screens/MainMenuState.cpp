#include "MainMenuState.hpp"
#include "GameState.hpp"

#include <iostream>
#include <utility>

MainMenuState::MainMenuState(GameDataRef data) : data(std::move(data)) {
}

void MainMenuState::init() {
    data->assets.loadTexture("mainScreen", "start_screen.png");
    data->assets.loadSound("mainSound", "main_screen.wav");
    background.setTexture(data->assets.getTexture("mainScreen"));

    const sf::Vector2f windowSize(
        static_cast<float>(data->window.getSize().x),
        static_cast<float>(data->window.getSize().y)
    );
    const sf::Vector2f textureSize(
        static_cast<float>(data->assets.getTexture("mainScreen").getSize().x),
        static_cast<float>(data->assets.getTexture("mainScreen").getSize().y)
    );

    sf::Vector2f scale;
    scale.x = windowSize.x / textureSize.x;
    scale.y = windowSize.y / textureSize.y;
    background.setScale(scale);

    // Center the sprite
    background.setOrigin(static_cast<float>(textureSize.x) / 2.0f,
        static_cast<float>(textureSize.y) / 2.0f);
    background.setPosition(static_cast<float>(windowSize.x) / 2.0f,
        static_cast<float>(windowSize.y) / 2.0f);

    data->sound.openFromFile(data->assets.getSound("mainSound"));
    data->sound.play();
}

void MainMenuState::handleInput() {
    sf::Event event{};
    while (data->window.pollEvent(event)) {
        if (InputManager::isClosedEvent(event) || InputManager::isEscPressed()) {
            data->window.close();
        }
    }
    if (InputManager::isEnterPressed()) {
        std::cout << "go to Game" << std::endl;
        data->sound.stop();
        data->fsm.addState(StateRef(new GameState(data)), true);
    }
}

void MainMenuState::update(const float dt) {
}

void MainMenuState::render(float dt) {
    data->window.clear(sf::Color::Black);
    data->window.draw(background);
    data->window.display();
}
