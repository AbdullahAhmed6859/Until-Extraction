#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
using std::string, std::map;


class AssetManager {
    map<string, sf::Texture> textures;
    map<string, sf::Font> fonts;
public:
    AssetManager();
    ~AssetManager();
    void loadTexture(const string &name, const string &fileName);
    void loadFont(const string &name, const string &fileName);
    sf::Font &getFont(const string &name);
    sf::Texture &getTexture(const string &name);
};



#endif //ASSETMANAGER_HPP
