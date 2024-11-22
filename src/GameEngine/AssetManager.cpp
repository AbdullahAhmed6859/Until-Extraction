#include "AssetManager.hpp"

AssetManager::AssetManager() = default;
AssetManager::~AssetManager() = default;

void AssetManager::loadTexture(const string& name, const string& fileName) {
    sf::Texture tex;
    if (tex.loadFromFile("../assets/textures/" + fileName)) {
        textures[name] = tex;
    }
}

void AssetManager::loadFont(const string& name, const string& fileName) {
    sf::Font font;
    if (font.loadFromFile("../assets/fonts/" + fileName)) {
        fonts[name] = font;
    }
}

void AssetManager::loadSound(const string& name, const string& fileName) {
    sounds[name] = "../assets/audio/" + fileName;
}

sf::Texture& AssetManager::getTexture(const string& name) {
    return textures.at(name);
}

sf::Font& AssetManager::getFont(const string& name) {
    return fonts.at(name);
}

string AssetManager::getSound(const string& name) {
    return sounds.at(name);
}