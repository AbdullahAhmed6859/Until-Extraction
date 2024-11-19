#include "SplashScreenState.hpp"
#include <iostream>
#include <utility>

SplashScreenState::SplashScreenState(GameDataRef data) : data(std::move(data)) {
    scaleSpeed = sf::Vector2f(0.04f, 0.04f);
}

void SplashScreenState::init() {
    data->assets.loadTexture("splashScreen", "splash_screen.jpg");

    background.setTexture(data->assets.getTexture("splashScreen"));

    const sf::Vector2f windowSize(
        static_cast<float>(data->window.getSize().x),
        static_cast<float>(data->window.getSize().y)
    );
    const sf::Vector2f textureSize(
        static_cast<float>(data->assets.getTexture("splashScreen").getSize().x),
        static_cast<float>(data->assets.getTexture("splashScreen").getSize().y)
    );

    scale.x = windowSize.x / textureSize.x;
    scale.y = windowSize.y / textureSize.y;
    background.setScale(scale);

    // Center the sprite
    background.setOrigin(static_cast<float>(textureSize.x) / 2.0f,
        static_cast<float>(textureSize.y) / 2.0f);
    background.setPosition(static_cast<float>(windowSize.x) / 2.0f,
        static_cast<float>(windowSize.y) / 2.0f);
}

void SplashScreenState::handleInput() {
    sf::Event event{};
    while (data->window.pollEvent(event)) {
        if (InputManager::isClosedEvent(event) || InputManager::isEscPressed()) {
            data->window.close();
        }
    }
}

void SplashScreenState::update(const float dt) {
    constexpr float SPLASH_SCREEN_DURATION = 4.0f;

    if (clock.getElapsedTime().asSeconds() >= SPLASH_SCREEN_DURATION) {
        std::cout << "go to main menu" << std::endl;
        // data->fsm.addState(StateRef(new MainMenuState(data)), true);
    } else {
        scale += scaleSpeed * dt;
        scaleSpeed = scaleSpeed * 0.99f;
        background.setScale(scale);

        const sf::Vector2f textureSize(
            static_cast<float>(data->assets.getTexture("splashScreen").getSize().x),
            static_cast<float>(data->assets.getTexture("splashScreen").getSize().y)
        );
        const sf::Vector2f windowSize(
            static_cast<float>(data->window.getSize().x),
            static_cast<float>(data->window.getSize().y)
        );

        background.setOrigin(static_cast<float>(textureSize.x) / 2.0f,
            static_cast<float>(textureSize.y) / 2.0f);
        background.setPosition(static_cast<float>(windowSize.x) / 2.0f,
            static_cast<float>(windowSize.y) / 2.0f);
    }
}

void SplashScreenState::render(float dt) {
    data->window.clear(sf::Color::Black);
    data->window.draw(background);
    data->window.display();
}
