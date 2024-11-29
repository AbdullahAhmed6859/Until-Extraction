#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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
    sf::Texture hero;
    sf::Texture hero2;
    sf::Texture hero3;
    sf::Texture hero4;
    sf::Texture hero5;
    sf::Texture hero6;
    sf::Texture hero7;
    sf::Texture shoot;
    sf::Texture shoot2;
    sf::Texture shoot3;
    sf::Texture shoot4;
    sf::Texture idle;
    sf::Texture wake1;
    sf::Texture wake2;
    sf::Texture wake3;
    sf::Texture wake4;

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
    

    sf::Sprite heroSprite;
    sf::Vector2f heroPosition;
    float heroSpeed = 200.0f; // Pixels per second

    float animationTimer = 0.0f;
    int currentFrame = 0;
    const float FRAME_TIME = 0.2f; // Time between frame changes
    bool isMoving = false;

    enum Direction { Left, Right };
    Direction currentDirection = Right;

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

    const int HERO_WIDTH = 38;
    const int HERO_HEIGHT = 26;

    bool isShooting = false;
    int shootFrame = 0;
    const float SHOOT_FRAME_TIME = 0.07f; // Faster than walking animation
    float shootTimer = 0.0f;

    const int SHOOT_WIDTH = 50;
    const int SHOOT_HEIGHT = 26;

    enum class GameState {
        Running,
        Pausing,
        Paused,
        Resuming
    };
    GameState gameState = GameState::Running;
    float wakeTimer = 0.0f;
    int wakeFrame = 0;
    const float WAKE_FRAME_TIME = 0.2f;
    bool hasCompletedStartup = false;

public:
    // Constructor: Initialize camera with the given view size
    TileMap(const sf::Vector2f &viewSize) {
    float centerX = ((MAP_WIDTH + map_lowerbound_width)/2) * TILE_SIZE;
    float centerY = ((MAP_HEIGHT + map_lowerbound_height)/2) * TILE_SIZE;
    heroPosition = sf::Vector2f(centerX + TILE_SIZE/2, centerY + TILE_SIZE/2);
    camera.setCenter(centerX + TILE_SIZE/2, centerY + TILE_SIZE/2);
    gameState = GameState::Running;  // Start directly in running state
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
        if (!hero.loadFromFile("../assets/tile0001.png")) {
            std::cout << "Failed to load hero!" << std::endl;
            return false;
        }
        if (!hero2.loadFromFile("../assets/tile004.png")) {
            std::cout << "Failed to load hero2!" << std::endl;
            return false;
        }
        if (!hero3.loadFromFile("../assets/tile008.png")) {
            std::cout << "Failed to load hero3!" << std::endl;
            return false;
        }
        if (!hero4.loadFromFile("../assets/tile012.png")) {
            std::cout << "Failed to load hero4!" << std::endl;
            return false;
        }
        if (!hero5.loadFromFile("../assets/tile016.png")) {
            std::cout << "Failed to load hero5!" << std::endl;
            return false;
        }
        if (!hero6.loadFromFile("../assets/tile020.png")) {
            std::cout << "Failed to load hero6!" << std::endl;
            return false;
        }
        if (!hero7.loadFromFile("../assets/tile024.png")) {
            std::cout << "Failed to load hero7!" << std::endl;
            return false;
        }
        if (!shoot.loadFromFile("../assets/shoot.png")) {
            std::cout << "Failed to load shoot animation!" << std::endl;
            return false;
        }
        if (!shoot2.loadFromFile("../assets/shoot2.png")) {
            std::cout << "Failed to load shoot2 animation!" << std::endl;
            return false;
        }
        if (!shoot3.loadFromFile("../assets/shoot3.png")) {
            std::cout << "Failed to load shoot3 animation!" << std::endl;
            return false;
        }
        if (!shoot4.loadFromFile("../assets/shoot4.png")) {
            std::cout << "Failed to load shoot4 animation!" << std::endl;
            return false;
        }
        if(!idle.loadFromFile("../assets/idle.png")) {
            std::cout << "Failed to load idle animation!" << std::endl;
            return false;
        }
        if(!wake1.loadFromFile("../assets/wake1.png")) {
            std::cout << "Failed to load wake1 animation!" << std::endl;
            return false;
        }
        if(!wake2.loadFromFile("../assets/wake2.png")) {
            std::cout << "Failed to load wake2 animation!" << std::endl;
            return false;
        }
        if(!wake3.loadFromFile("../assets/wake3.png")) {
            std::cout << "Failed to load wake3 animation!" << std::endl;
            return false;
        }
        if(!wake4.loadFromFile("../assets/wake4.png")) {
            std::cout << "Failed to load wake4 animation!" << std::endl;
            return false;
        }

        heroSprite.setTexture(hero);  // Start with hero texture
        heroSprite.setOrigin(HERO_WIDTH / 2.0f, HERO_HEIGHT / 2.0f);

        // Set scale to match tile size if desired
        float scaleX = static_cast<float>(TILE_SIZE) / HERO_WIDTH;
        float scaleY = static_cast<float>(TILE_SIZE) / HERO_HEIGHT;
        heroSprite.setScale(scaleX, scaleY);

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
    void updateHeroAndCamera(float deltaTime) {
        static bool escapeReleased = true;

        // Handle pause toggle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            if (escapeReleased) {
                if (gameState == GameState::Running) {
                    gameState = GameState::Pausing;
                    wakeFrame = 0;
                    wakeTimer = 0.0f;
                } else if (gameState == GameState::Paused) {
                    gameState = GameState::Resuming;
                    wakeFrame = 0;
                    wakeTimer = 0.0f;
                }
                escapeReleased = false;
            }
        } else {
            escapeReleased = true;
        }

        // Handle pause animations
        wakeTimer += deltaTime;

        if (gameState == GameState::Pausing) {
            if (wakeTimer >= WAKE_FRAME_TIME) {
                wakeTimer = 0.0f;
                switch (wakeFrame) {
                    case 0: heroSprite.setTexture(wake4); break;
                    case 1: heroSprite.setTexture(wake3); break;
                    case 2: heroSprite.setTexture(wake2); break;
                    case 3: heroSprite.setTexture(wake1); break;
                    case 4: 
                        heroSprite.setTexture(idle);
                        gameState = GameState::Paused;
                        break;
                }
                wakeFrame++;
            }
            return;
        }

        if (gameState == GameState::Resuming) {
            if (wakeTimer >= WAKE_FRAME_TIME) {
                wakeTimer = 0.0f;
                switch (wakeFrame) {
                    case 0: heroSprite.setTexture(wake1); break;
                    case 1: heroSprite.setTexture(wake2); break;
                    case 2: heroSprite.setTexture(wake3); break;
                    case 3: heroSprite.setTexture(wake4); break;
                    case 4: 
                        heroSprite.setTexture(hero);
                        gameState = GameState::Running;
                        break;
                }
                wakeFrame++;
            }
            return;
        }

        if (gameState != GameState::Running) {
            return;
        }

        float moveDistance = heroSpeed * deltaTime;
        bool moved = false;
        
        // Update both animation timers
        animationTimer += deltaTime;
        shootTimer += deltaTime;

        // Handle shooting
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isShooting) {
            isShooting = true;
            shootFrame = 0;
            shootTimer = 0.0f;
        }

        // Process shooting animation
        if (isShooting) {
            if (shootTimer >= SHOOT_FRAME_TIME) {
                shootTimer = 0;
                // Cycle through shooting frames while maintaining hero dimensions
                switch (shootFrame) {
                    case 0: 
                        heroSprite.setTexture(shoot);
                        heroSprite.setOrigin(HERO_WIDTH / 2.0f, HERO_HEIGHT / 2.0f);
                        heroSprite.setScale((static_cast<float>(TILE_SIZE) / HERO_WIDTH) * 
                            (currentDirection == Left ? -1.0f : 1.0f),
                            static_cast<float>(TILE_SIZE) / HERO_HEIGHT);
                        break;
                    case 1: 
                        heroSprite.setTexture(shoot2);
                        heroSprite.setOrigin(HERO_WIDTH / 2.0f, HERO_HEIGHT / 2.0f);
                        heroSprite.setScale((static_cast<float>(TILE_SIZE) / HERO_WIDTH) * 
                            (currentDirection == Left ? -1.0f : 1.0f),
                            static_cast<float>(TILE_SIZE) / HERO_HEIGHT);
                        break;
                    case 2: 
                        heroSprite.setTexture(shoot3);
                        heroSprite.setOrigin(HERO_WIDTH / 2.0f, HERO_HEIGHT / 2.0f);
                        heroSprite.setScale((static_cast<float>(TILE_SIZE) / HERO_WIDTH) * 
                            (currentDirection == Left ? -1.0f : 1.0f),
                            static_cast<float>(TILE_SIZE) / HERO_HEIGHT);
                        break;
                    case 3: 
                        heroSprite.setTexture(shoot4);
                        heroSprite.setOrigin(HERO_WIDTH / 2.0f, HERO_HEIGHT / 2.0f);
                        heroSprite.setScale((static_cast<float>(TILE_SIZE) / HERO_WIDTH) * 
                            (currentDirection == Left ? -1.0f : 1.0f),
                            static_cast<float>(TILE_SIZE) / HERO_HEIGHT);
                        break;
                }
                shootFrame++;
                
                // End shooting animation after 4 frames
                if (shootFrame >= 4) {
                    isShooting = false;
                    heroSprite.setTexture(hero);
                    heroSprite.setOrigin(HERO_WIDTH / 2.0f, HERO_HEIGHT / 2.0f);
                    heroSprite.setScale((static_cast<float>(TILE_SIZE) / HERO_WIDTH) * 
                        (currentDirection == Left ? -1.0f : 1.0f),
                        static_cast<float>(TILE_SIZE) / HERO_HEIGHT);
                }
            }
        }
        // Only do walking animation if not shooting
        else if (!isMoving) {
            currentFrame = 0;
            heroSprite.setTexture(hero);
        }

        // Track horizontal direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  // Left
            currentDirection = Left;
            heroSprite.setScale(-std::abs(heroSprite.getScale().x), heroSprite.getScale().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  // Right
            currentDirection = Right;
            heroSprite.setScale(std::abs(heroSprite.getScale().x), heroSprite.getScale().y);
        }

        // Diagonal movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            heroPosition += sf::Vector2f(-moveDistance / sqrt(2), -moveDistance / sqrt(2));
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            heroPosition += sf::Vector2f(moveDistance / sqrt(2), -moveDistance / sqrt(2));
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            heroPosition += sf::Vector2f(-moveDistance / sqrt(2), moveDistance / sqrt(2));
            moved = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            heroPosition += sf::Vector2f(moveDistance / sqrt(2), moveDistance / sqrt(2));
            moved = true;
        }
        // Cardinal movement
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  // Left
                heroPosition.x -= moveDistance;
                moved = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  // Right
                heroPosition.x += moveDistance;
                moved = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {  // Up
                heroPosition.y -= moveDistance;
                moved = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  // Down
                heroPosition.y += moveDistance;
                moved = true;
            }
        }

        // Handle animation with direction
        if (moved && !isShooting) {
            isMoving = true;
            if (animationTimer >= FRAME_TIME) {
                animationTimer = 0;
                currentFrame = (currentFrame + 1) % 7;
                
                // Update texture based on current frame
                switch (currentFrame) {
                    case 0: heroSprite.setTexture(hero); break;
                    case 1: heroSprite.setTexture(hero2); break;
                    case 2: heroSprite.setTexture(hero3); break;
                    case 3: heroSprite.setTexture(hero4); break;
                    case 4: heroSprite.setTexture(hero5); break;
                    case 5: heroSprite.setTexture(hero6); break;
                    case 6: heroSprite.setTexture(hero7); break;
                }

                // Maintain direction
                float scaleX = std::abs(heroSprite.getScale().x);
                heroSprite.setScale(currentDirection == Left ? -scaleX : scaleX, heroSprite.getScale().y);
            }
        } else if (!isShooting) {
            isMoving = false;
        }

        // Clamp hero position to map boundaries
        heroPosition.x = std::max(static_cast<float>(map_lowerbound_width * TILE_SIZE + TILE_SIZE), 
                                std::min(heroPosition.x, static_cast<float>((MAP_WIDTH - 1) * TILE_SIZE)));
        heroPosition.y = std::max(static_cast<float>(map_lowerbound_height * TILE_SIZE + TILE_SIZE), 
                                std::min(heroPosition.y, static_cast<float>((MAP_HEIGHT - 1) * TILE_SIZE)));

        // Update hero sprite position
        heroSprite.setPosition(heroPosition);

        // Update camera to follow hero
        camera.setCenter(heroPosition);

        // Handle zoom
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
        window.draw(heroSprite);
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
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        map.updateHeroAndCamera(deltaTime);

        window.clear(sf::Color::Black);
        map.draw(window);
        window.display();
    }

    return 0;
}
