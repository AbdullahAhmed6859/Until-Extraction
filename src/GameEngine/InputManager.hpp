
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include <SFML/Graphics.hpp>

class InputManager {
public:
    InputManager();
    ~InputManager();
    static bool isSpriteClicked(const sf::Sprite& object, const sf::Mouse::Button& button, sf::RenderWindow& window);
    static sf::Vector2i getMousePosition(sf::RenderWindow &window);
    static bool isClosedEvent(const sf::Event &event);
    static bool isEscPressed();
    static bool isEnterPressed();
};



#endif //INPUTMANAGER_HPP
