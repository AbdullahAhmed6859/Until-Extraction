#include "InputManager.hpp"

InputManager::InputManager() = default;
InputManager::~InputManager() = default;

bool InputManager::isSpriteClicked(const sf::Sprite& object, const sf::Mouse::Button& button, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(button)) {
        const sf::IntRect tempRect = {
            static_cast<int>(object.getPosition().x),
            static_cast<int>(object.getPosition().y),
            object.getGlobalBounds().width,
            object.getGlobalBounds().height
        };

        if (tempRect.contains(sf::Mouse::getPosition(window)))
            return true;
    }
    return false;
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}

bool InputManager::isClosedEvent(const sf::Event &event) {
    return event.type == sf::Event::Closed;
}

bool InputManager::isEscPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

bool InputManager::isEnterPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}