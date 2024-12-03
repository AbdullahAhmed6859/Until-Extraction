#include "Game.hpp"

// #include "../../cmake-build-debug/_deps/sfml-src/extlibs/headers/AL/alc.h"
#include "../Screens/SplashScreenState.hpp"
#include "SFML/Audio/Listener.hpp"

Game::Game(const unsigned int width, const unsigned int height, const string &title): dt(1.0 / 60.0) {
    data = std::make_shared<GameData>();
    data->window.create(sf::VideoMode(width, height), title);
    data->fsm.addState(StateRef(new SplashScreenState(data)));
}

Game::Game(const string &title) : dt(1.0 / 60.0) {
    data = std::make_shared<GameData>();
    data->window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
    data->fsm.addState(StateRef(new SplashScreenState(data)));
}

Game::~Game() {
    sf::Listener::setGlobalVolume(0);
    data.reset();
    // ALCdevice* device = alcGetContextsDevice(alcGetCurrentContext());
    // if (device) {
    //     alcMakeContextCurrent(nullptr); // Detach the context
    //     alcCloseDevice(device);         // Close the device
    // }
}

void Game::run() const {
    float currentTime = clock.getElapsedTime().asSeconds();
    float acc = 0.0;

    while (data->window.isOpen()) {
        data->fsm.processStateChanges();
        const float newTime = clock.getElapsedTime().asSeconds();
        float frameTime = newTime - currentTime;

        if (frameTime > 0.25) frameTime = 0.25;
        currentTime = newTime;
        acc += frameTime;

        while (acc >= dt) {
            data->fsm.getCurrentState()->handleInput();
            this->data->fsm.getCurrentState()->update(dt);
            acc -= dt;
        }
        const float interpolationTime = acc / dt;
        data->fsm.getCurrentState()->render(interpolationTime);
    }
}