#include "AssetManager.hpp"

AssetManager::AssetManager() = default;
AssetManager::~AssetManager() = default;

void AssetManager::loadTexture(const string& name, const string& fileName) {
    sf::Texture tex;
    if (tex.loadFromFile(fileName)) {
        textures[name] = tex;
    }
}

void AssetManager::loadFont(const string& name, const string& fileName) {
    sf::Font font;
    if (font.loadFromFile(fileName)) {
        fonts[name] = font;
    }
}

sf::Texture& AssetManager::getTexture(const string& name) {
    return textures.at(name);
}

sf::Font& AssetManager::getFont(const string& name) {
    return fonts.at(name);
}