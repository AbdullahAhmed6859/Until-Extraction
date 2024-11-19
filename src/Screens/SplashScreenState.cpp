#include "SplashScreenState.hpp"

#include <iostream>
#include <sstream>
#include <utility>

SplashScreenState::SplashScreenState(GameDataRef data): data(std::move(data)) {
}

void SplashScreenState::init() {
    // Load the splash screen texture
    data->assets.loadTexture("splashScreen", "../assets/splash_screen.jpg");

    // Set the texture to the background sprite
    background.setTexture(data->assets.getTexture("splashScreen"));

    // Get the size of the window
    const sf::Vector2u windowSize = data->window.getSize();

    // Get the size of the texture
    const sf::Vector2u textureSize = data->assets.getTexture("splashScreen").getSize();

    // Calculate scale factors
    const float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    const float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Scale the sprite to fit the window
    background.setScale(scaleX, scaleY);
}


void SplashScreenState::handleInput() {
    sf::Event event{};

    while (data->window.pollEvent(event)) {
         if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
             data->window.close();
         }
    }
}

void SplashScreenState::update(float dt) {
    if (clock.getElapsedTime().asSeconds() >= 3) {
        std:: cout << "go to main menu" << std::endl;
    }
}

void SplashScreenState::render(float dt) {
    data->window.clear(sf::Color::Black);
    data->window.draw(background);
    data->window.display();
}
