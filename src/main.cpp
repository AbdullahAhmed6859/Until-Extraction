#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class TileMap {
private:
    // Core resources
    sf::Texture texture; 
    sf::Texture space;     // Stores the single tile texture
    sf::Texture toptxtr;
    sf::Texture tltxtr;
    sf::Texture trtxtr;
    sf::Texture ltxtr;
    sf::Texture rtxtr;
    sf::Texture btmtxtr;
    sf::Texture btmltxtr;
    sf::Texture btmrtxtr;
    std::vector<sf::Sprite> tiles; // Container for all map tiles
    std::vector<sf::Sprite> stiles;
    std::vector<sf::Sprite> toptiles;
    std::vector<sf::Sprite> tltiles;
    std::vector<sf::Sprite> trtiles;
    std::vector<sf::Sprite> ltiles;
    std::vector<sf::Sprite> rtiles;
    std::vector<sf::Sprite> btmtiles;
    std::vector<sf::Sprite> btmltiles;
    std::vector<sf::Sprite> btmrtiles;

    // Map configuration
    const int TILE_SIZE = 32;  // Size of each tile in pixels
    const int MAP_WIDTH = 40*2;  // Number of tiles horizontally
    const int MAP_HEIGHT = 30*2; // Number of tiles vertically
    int map_lowerbound_width  = MAP_WIDTH / 2;
    int map_lowerbound_height = MAP_HEIGHT / 2;
    int Map_boundary_width = MAP_WIDTH * 4;
    int Map_boundary_height = MAP_HEIGHT * 4;

    // Camera settings
    sf::View camera;            // SFML View for camera control
    float cameraSpeed = 500.0f; // Camera movement speed (pixels/second)

public:
    // Constructor: Initialize camera with the given view size
    TileMap(const sf::Vector2f &viewSize){
    float centerX = ((MAP_WIDTH + map_lowerbound_width)/2 );
    float centerY = ((MAP_HEIGHT + map_lowerbound_height)/2 );
    camera.setCenter(centerX, centerY);
}

    // Initialize the tilemap and load resources
    bool initialize() {
        // Load the single tile texture
        if (!texture.loadFromFile("../assets/tile014.png")) {
            std::cout << "Failed to load tile texture!" << std::endl;
            return false;
        }
        if (!space.loadFromFile("../assets/Space_Stars4.png")) {
            std::cout << "Failed to load space tile texture!" << std::endl;
            return false;
        }
        if (!toptxtr.loadFromFile("../assets/tile040.png")) {
            std::cout << "Failed to load top tile texture!" << std::endl;
            return false;
        }
        if (!tltxtr.loadFromFile("../assets/tile039.png")) {
            std::cout << "Failed to load top left tile texture!" << std::endl;
            return false;
        }
        if (!trtxtr.loadFromFile("../assets/tile041.png")) {
            std::cout << "Failed to load top right tile texture!" << std::endl;
            return false;
        }
        if (!ltxtr.loadFromFile("../assets/tile052.png")) {
            std::cout << "Failed to load left tile texture!" << std::endl;
            return false;
        }
        if (!rtxtr.loadFromFile("../assets/tile054.png")) {
            std::cout << "Failed to load right tile texture!" << std::endl;
            return false;
        }
        if (!btmtxtr.loadFromFile("../assets/tile066.png")) {
            std::cout << "Failed to load bottom tile texture!" << std::endl;
            return false;
        }
        if (!btmltxtr.loadFromFile("../assets/tile065.png")) {
            std::cout << "Failed to load bottom left tile texture!" << std::endl;
            return false;
        }
        if (!btmrtxtr.loadFromFile("../assets/tile067.png")) {
            std::cout << "Failed to load bottom right tile texture!" << std::endl;
            return false;
        }

        generateMap();
        return true;
    }

    // Generate a map filled with duplicated tiles
    void generateMap() {
    tiles.clear();
    stiles.clear();
    toptiles.clear();
    tltiles.clear();
    trtiles.clear();
    ltiles.clear();
    rtiles.clear();
    btmtiles.clear();
    btmltiles.clear();
    btmrtiles.clear();

    for (int y = 0; y < Map_boundary_height; ++y) {
        for (int x = 0; x < Map_boundary_width; ++x) {
            sf::Sprite tile;
            
            
            if (y == map_lowerbound_height || y == MAP_HEIGHT - 1) {
                // Top and bottom border tiles
                if (x == map_lowerbound_width && y == map_lowerbound_height) {
                    tile.setTexture(tltxtr);
                    tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    tltiles.push_back(tile);
                } else if (y == map_lowerbound_height && x == MAP_WIDTH - 1) {
                    tile.setTexture(trtxtr);
                    tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    trtiles.push_back(tile);
                } else if (y == map_lowerbound_height && x < MAP_WIDTH && x > map_lowerbound_width) {
                    tile.setTexture(toptxtr);
                    tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    toptiles.push_back(tile);
                } 
                 else if (y == MAP_HEIGHT -1 && x > map_lowerbound_width && x < MAP_WIDTH - 1) {
                    tile.setTexture(btmtxtr);
                    tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    btmtiles.push_back(tile); 
                 }
                else if (y == MAP_HEIGHT -1 && x == map_lowerbound_width) {
                    tile.setTexture(btmltxtr);
                    tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    btmltiles.push_back(tile); 
                }
                else if (y == MAP_HEIGHT -1 && x == MAP_WIDTH - 1) {
                    tile.setTexture(btmrtxtr);
                    tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    btmrtiles.push_back(tile); 
                }
                else {
                    
                    tile.setTexture(space);
                    tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    stiles.push_back(tile);
                }
            } else if (x == map_lowerbound_width and y < MAP_HEIGHT && y > map_lowerbound_height) {
                // Left border tiles
                tile.setTexture(ltxtr);
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                ltiles.push_back(tile);
            } else if (x == MAP_WIDTH - 1 && y < MAP_HEIGHT && y > map_lowerbound_height) {
                // Right border tiles
                tile.setTexture(rtxtr);
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                rtiles.push_back(tile);
            } else if (x < MAP_WIDTH && y < MAP_HEIGHT && x > map_lowerbound_width && y > map_lowerbound_height) {
                // Inner tiles
                tile.setTexture(texture);
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                tiles.push_back(tile);
            } else {
                // Space tiles outside the main map boundaries
                
                tile.setTexture(space);
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                stiles.push_back(tile);
            }
        }
    }
}

    // Update camera position based on input
    void updateCamera(float deltaTime, const sf::RenderWindow &window) {
        float moveSpeed = cameraSpeed * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            camera.move(-moveSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            camera.move(moveSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            camera.move(0, -moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            camera.move(0, moveSpeed);

        // Calculate the boundaries of the map
    
    float leftBound = map_lowerbound_width*TILE_SIZE;
    float rightBound = MAP_WIDTH*TILE_SIZE;
    float topBound = map_lowerbound_height*TILE_SIZE;
    float bottomBound = MAP_HEIGHT*TILE_SIZE;

    // Clamp the camera position within the map boundaries
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(leftBound, std::min(cameraCenter.x, rightBound));
    cameraCenter.y = std::max(topBound, std::min(cameraCenter.y, bottomBound));
    camera.setCenter(cameraCenter);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            camera.zoom(0.99f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            camera.zoom(1.01f);
    }

    // Draw the map
    void draw(sf::RenderWindow &window) {
        window.setView(camera);

        for (const auto &tile : tiles) {
            window.draw(tile);
        }
        for (const auto &tile : stiles) {
            window.draw(tile);
        }
        for (const auto &tile : toptiles) {
            window.draw(tile);
        }
        for (const auto &tile : tltiles) {
            window.draw(tile);
        }
        for (const auto &tile : trtiles) {
            window.draw(tile);
        }
        for (const auto &tile : ltiles) {
            window.draw(tile);
        }
        for (const auto &tile : rtiles) {
            window.draw(tile);
        }
        for (const auto &tile : btmtiles) {
            window.draw(tile);
        }
        for (const auto &tile : btmltiles) {
            window.draw(tile);
        }
        for (const auto &tile : btmrtiles) {
            window.draw(tile);
        }
    }
};

int main() {
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Duplicated Tilemap");
    window.setFramerateLimit(60);

    TileMap map(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    if (!map.initialize()) {
        std::cout << "Failed to initialize the tilemap!" << std::endl;
        return 1;
    }

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        map.updateCamera(deltaTime, window);

        window.clear(sf::Color::Black);
        map.draw(window);
        window.display();
    }

    return 0;
}
