#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class TileMap {
private:
    // Core resources
    sf::Texture texture;
    sf::Texture space; // Stores the single tile texture
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
    sf::Texture spaceshipdmged;
    sf::Texture tree;
    sf::Texture tree2;
    sf::Texture tree3;
    sf::Texture idlet;
    sf::Texture idle2;
    sf::Texture idle3;
    sf::Texture idle4;
    sf::Texture attack;
    sf::Texture attack2;
    sf::Texture attack3;
    sf::Texture attack4;
    sf::Texture attack5;
    sf::Texture attack6;
    sf::Texture death;
    sf::Texture death2;
    sf::Texture death3;
    sf::Texture death4;
    sf::Texture death5;
    sf::Texture death6;
    sf::Texture death7;
    sf::Texture walk;
    sf::Texture walk2;
    sf::Texture walk3;
    sf::Texture walk4;
    sf::Texture walk5;
    sf::Texture walk6;

    // Player health attributes
    std::vector<sf::Texture> healthBarTextures;
    sf::Sprite healthBarSprite;
    int currentHealth = 100;
    int maxHealth = 100;
    float healthBarTimer = 0.0f;
    const float HEALTH_BAR_FRAME_TIME = 0.2f;

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
    std::vector<sf::Sprite> spaceshipdmg;
    std::vector<sf::Sprite> trees;
    std::vector<sf::Sprite> trees2;
    std::vector<sf::Sprite> trees3;
    std::vector<sf::Sprite> idles;
    std::vector<sf::Sprite> idles2;
    std::vector<sf::Sprite> idles3;
    std::vector<sf::Sprite> idles4;
    std::vector<sf::Sprite> attacks;
    std::vector<sf::Sprite> attacks2;
    std::vector<sf::Sprite> attacks3;
    std::vector<sf::Sprite> attacks4;
    std::vector<sf::Sprite> attacks5;
    std::vector<sf::Sprite> attacks6;
    std::vector<sf::Sprite> deaths;
    std::vector<sf::Sprite> deaths2;
    std::vector<sf::Sprite> deaths3;
    std::vector<sf::Sprite> deaths4;
    std::vector<sf::Sprite> deaths5;
    std::vector<sf::Sprite> deaths6;
    std::vector<sf::Sprite> deaths7;
    std::vector<sf::Sprite> walks;
    std::vector<sf::Sprite> walks2;
    std::vector<sf::Sprite> walks3;
    std::vector<sf::Sprite> walks4;
    std::vector<sf::Sprite> walks5;
    std::vector<sf::Sprite> walks6;

    sf::Sprite heroSprite;
    sf::Vector2f heroPosition;
    float heroSpeed = 200.0f; // Pixels per second

    float animationTimer = 0.0f;
    int currentFrame = 0;
    const float FRAME_TIME = 0.2f; // Time between frame changes
    bool isMoving = false;

    enum Direction {
        Left,
        Right
    };
    Direction currentDirection = Right;

    // Map configuration
    const int TILE_SIZE = 32;      // Size of each tile in pixels
    const int MAP_WIDTH = 40 * 2;  // Number of tiles horizontally
    const int MAP_HEIGHT = 30 * 2; // Number of tiles vertically
    int map_lowerbound_width = MAP_WIDTH / 2;
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

    sf::Sprite spaceshipSprite;
    sf::Vector2f spaceshipPosition;
    const float SPACESHIP_WIDTH = 32.0f;
    const float SPACESHIP_HEIGHT = 32.0f;

    const float COLLISION_RADIUS = 32.0f; // Collision radius for spaceship

    // Add tree dimensions as constants in private section:
    const float TREE_WIDTH = 180.0f;
    const float TREE_HEIGHT = 256.0f;

public:
    // Constructor: Initialize camera with the given view size
    TileMap(const sf::Vector2f &viewSize) {
        // Set spaceship position near center of map
        float centerX = ((MAP_WIDTH + map_lowerbound_width) / 2) * TILE_SIZE;
        float centerY = ((MAP_HEIGHT + map_lowerbound_height) / 2) * TILE_SIZE;
        spaceshipPosition = sf::Vector2f(centerX, centerY);

        // Set hero position to start to the right of spaceship
        // Add TILE_SIZE * 2 to x position to place hero 2 tiles right of spaceship
        heroPosition = sf::Vector2f(centerX + TILE_SIZE * 2, centerY);

        // Center camera on spaceship/hero position
        camera.setCenter(centerX + TILE_SIZE, centerY);
        gameState = GameState::Running;
    }
    void updateHealth(int damage, float deltaTime) {
        currentHealth -= damage;
        if(currentHealth < 0){
            currentHealth = 0;
        }
        int frameIndex = (currentHealth * (healthBarTextures.size() - 1)) / maxHealth;
        healthBarSprite.setTexture(healthBarTextures[frameIndex]);
    }

    // Initialize the tilemap and load resources
    bool initialize() {
        // Loading health bar textures
        for (int i = 1; i <= 11; i++) { // Assuming 5 frames for health bar animation
            sf::Texture texture;
            std::string filePath = "../assets/health" + std::to_string(i) + ".png";
            if (!texture.loadFromFile(filePath)) {
                std::cout << "Failed to load health bar texture: " << filePath << std::endl;
                return false;
            }
            healthBarTextures.push_back(std::move(texture));
        }

        // Set initial health bar sprite
        healthBarSprite.setTexture(healthBarTextures[10]);
        healthBarSprite.setScale(2.0f, 2.0f);      // Scale for better visibility
        healthBarSprite.setPosition(10.0f, 10.0f); // Position on the screen

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
        if (!idle.loadFromFile("../assets/idle.png")) {
            std::cout << "Failed to load idle animation!" << std::endl;
            return false;
        }
        if (!wake1.loadFromFile("../assets/wake1.png")) {
            std::cout << "Failed to load wake1 animation!" << std::endl;
            return false;
        }
        if (!wake2.loadFromFile("../assets/wake2.png")) {
            std::cout << "Failed to load wake2 animation!" << std::endl;
            return false;
        }
        if (!wake3.loadFromFile("../assets/wake3.png")) {
            std::cout << "Failed to load wake3 animation!" << std::endl;
            return false;
        }
        if (!wake4.loadFromFile("../assets/wake4.png")) {
            std::cout << "Failed to load wake4 animation!" << std::endl;
            return false;
        }
        if (!spaceshipdmged.loadFromFile("../assets/spaceship.png")) {
            std::cout << "Failed to load spaceshipdmged animation!" << std::endl;
            return false;
        }
        if (!tree.loadFromFile("../assets/tree.png")) {
            std::cout << "Failed to load tree animation!" << std::endl;
            return false;
        }
        if (!tree2.loadFromFile("../assets/tree2.png")) {
            std::cout << "Failed to load tree2 animation!" << std::endl;
            return false;
        }
        if (!tree3.loadFromFile("../assets/tree3.png")) {
            std::cout << "Failed to load tree3 animation!" << std::endl;
            return false;
        }
        if (!idlet.loadFromFile("../assets/idle.png")) {
            std::cout << "Failed to load idlet animation!" << std::endl;
            return false;
        }
        if (!idle2.loadFromFile("../assets/idle2.png")) {
            std::cout << "Failed to load idle2 animation!" << std::endl;
            return false;
        }
        if (!idle3.loadFromFile("../assets/idle3.png")) {
            std::cout << "Failed to load idle3 animation!" << std::endl;
            return false;
        }
        if (!idle4.loadFromFile("../assets/idle4.png")) {
            std::cout << "Failed to load idle4 animation!" << std::endl;
            return false;
        }
        if (!attack.loadFromFile("../assets/attack.png")) {
            std::cout << "Failed to load attack animation!" << std::endl;
            return false;
        }
        if (!attack2.loadFromFile("../assets/attack2.png")) {
            std::cout << "Failed to load attack2 animation!" << std::endl;
            return false;
        }
        if (!attack3.loadFromFile("../assets/attack3.png")) {
            std::cout << "Failed to load attack3 animation!" << std::endl;
            return false;
        }
        if (!attack4.loadFromFile("../assets/attack4.png")) {
            std::cout << "Failed to load attack4 animation!" << std::endl;
            return false;
        }
        if (!attack5.loadFromFile("../assets/attack5.png")) {
            std::cout << "Failed to load attack5 animation!" << std::endl;
            return false;
        }
        if (!attack6.loadFromFile("../assets/attack6.png")) {
            std::cout << "Failed to load attack6 animation!" << std::endl;
            return false;
        }
        if (!death.loadFromFile("../assets/death.png")) {
            std::cout << "Failed to load death animation!" << std::endl;
            return false;
        }
        if (!death2.loadFromFile("../assets/death2.png")) {
            std::cout << "Failed to load death2 animation!" << std::endl;
            return false;
        }
        if (!death3.loadFromFile("../assets/death3.png")) {
            std::cout << "Failed to load death3 animation!" << std::endl;
            return false;
        }
        if (!death4.loadFromFile("../assets/death4.png")) {
            std::cout << "Failed to load death4 animation!" << std::endl;
            return false;
        }
        if (!death5.loadFromFile("../assets/death5.png")) {
            std::cout << "Failed to load death5 animation!" << std::endl;
            return false;
        }
        if (!death6.loadFromFile("../assets/death6.png")) {
            std::cout << "Failed to load death6 animation!" << std::endl;
            return false;
        }
        if (!death7.loadFromFile("../assets/death7.png")) {
            std::cout << "Failed to load death7 animation!" << std::endl;
            return false;
        }
        if (!walk.loadFromFile("../assets/walk.png")) {
            std::cout << "Failed to load walk animation!" << std::endl;
            return false;
        }
        if (!walk2.loadFromFile("../assets/walk2.png")) {
            std::cout << "Failed to load walk2 animation!" << std::endl;
            return false;
        }
        if (!walk3.loadFromFile("../assets/walk3.png")) {
            std::cout << "Failed to load walk3 animation!" << std::endl;
            return false;
        }
        if (!walk4.loadFromFile("../assets/walk4.png")) {
            std::cout << "Failed to load walk4 animation!" << std::endl;
            return false;
        }
        if (!walk5.loadFromFile("../assets/walk5.png")) {
            std::cout << "Failed to load walk5 animation!" << std::endl;
            return false;
        }
        if (!walk6.loadFromFile("../assets/walk6.png")) {
            std::cout << "Failed to load walk6 animation!" << std::endl;
            return false;
        }

        // Setup spaceship sprite
        spaceshipSprite.setTexture(spaceshipdmged);
        spaceshipSprite.setOrigin(SPACESHIP_WIDTH / 2, SPACESHIP_HEIGHT / 2);
        spaceshipSprite.setPosition(spaceshipPosition);

        // Set scale to 1 to show at full size since texture is already 32x32
        spaceshipSprite.setScale(1.0f, 1.0f);

        // Setup hero at spaceship position
        heroSprite.setTexture(hero);
        heroSprite.setOrigin(HERO_WIDTH / 2.0f, HERO_HEIGHT / 2.0f);
        heroSprite.setPosition(heroPosition);
        float scaleX = static_cast<float>(TILE_SIZE) / HERO_WIDTH;
        float scaleY = static_cast<float>(TILE_SIZE) / HERO_HEIGHT;
        heroSprite.setScale(scaleX, scaleY);

        generateMap();
        createTrees();
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
                    } else if (y == MAP_HEIGHT - 1 && x > map_lowerbound_width && x < MAP_WIDTH - 1) {
                        tile.setTexture(btmtxtr);
                        tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                        btmtiles.push_back(tile);
                    } else if (y == MAP_HEIGHT - 1 && x == map_lowerbound_width) {
                        tile.setTexture(btmltxtr);
                        tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                        btmltiles.push_back(tile);
                    } else if (y == MAP_HEIGHT - 1 && x == MAP_WIDTH - 1) {
                        tile.setTexture(btmrtxtr);
                        tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                        btmrtiles.push_back(tile);
                    } else {

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            updateHealth(10, deltaTime);
        }
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
                case 0:
                    heroSprite.setTexture(wake4);
                    break;
                case 1:
                    heroSprite.setTexture(wake3);
                    break;
                case 2:
                    heroSprite.setTexture(wake2);
                    break;
                case 3:
                    heroSprite.setTexture(wake1);
                    break;
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
                case 0:
                    heroSprite.setTexture(wake1);
                    break;
                case 1:
                    heroSprite.setTexture(wake2);
                    break;
                case 2:
                    heroSprite.setTexture(wake3);
                    break;
                case 3:
                    heroSprite.setTexture(wake4);
                    break;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // Left
            currentDirection = Left;
            heroSprite.setScale(-std::abs(heroSprite.getScale().x), heroSprite.getScale().y);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
            currentDirection = Right;
            heroSprite.setScale(std::abs(heroSprite.getScale().x), heroSprite.getScale().y);
        }

        // Diagonal movement
        sf::Vector2f newPosition = heroPosition;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            newPosition += sf::Vector2f(-moveDistance / sqrt(2), -moveDistance / sqrt(2));
            if (!wouldCollideWithSpaceship(newPosition)) {
                heroPosition = newPosition;
                moved = true;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            newPosition += sf::Vector2f(moveDistance / sqrt(2), -moveDistance / sqrt(2));
            if (!wouldCollideWithSpaceship(newPosition)) {
                heroPosition = newPosition;
                moved = true;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            newPosition += sf::Vector2f(-moveDistance / sqrt(2), moveDistance / sqrt(2));
            if (!wouldCollideWithSpaceship(newPosition)) {
                heroPosition = newPosition;
                moved = true;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            newPosition += sf::Vector2f(moveDistance / sqrt(2), moveDistance / sqrt(2));
            if (!wouldCollideWithSpaceship(newPosition)) {
                heroPosition = newPosition;
                moved = true;
            }
        }
        // Cardinal movement
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // Left
                newPosition.x -= moveDistance;
                if (!wouldCollideWithSpaceship(newPosition)) {
                    heroPosition = newPosition;
                    moved = true;
                }
                newPosition = heroPosition;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
                newPosition.x += moveDistance;
                if (!wouldCollideWithSpaceship(newPosition)) {
                    heroPosition = newPosition;
                    moved = true;
                }
                newPosition = heroPosition;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // Up
                newPosition.y -= moveDistance;
                if (!wouldCollideWithSpaceship(newPosition)) {
                    heroPosition = newPosition;
                    moved = true;
                }
                newPosition = heroPosition;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // Down
                newPosition.y += moveDistance;
                if (!wouldCollideWithSpaceship(newPosition)) {
                    heroPosition = newPosition;
                    moved = true;
                }
                newPosition = heroPosition;
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
                case 0:
                    heroSprite.setTexture(hero);
                    break;
                case 1:
                    heroSprite.setTexture(hero2);
                    break;
                case 2:
                    heroSprite.setTexture(hero3);
                    break;
                case 3:
                    heroSprite.setTexture(hero4);
                    break;
                case 4:
                    heroSprite.setTexture(hero5);
                    break;
                case 5:
                    heroSprite.setTexture(hero6);
                    break;
                case 6:
                    heroSprite.setTexture(hero7);
                    break;
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

    // Add collision check method:
    bool wouldCollideWithSpaceship(const sf::Vector2f &newPosition) {
        // Get actual center of spaceship sprite
        sf::Vector2f spaceshipCenter = spaceshipSprite.getPosition();

        // Calculate distance from sprite centers
        float dx = newPosition.x - spaceshipCenter.x;
        float dy = newPosition.y - spaceshipCenter.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        return distance < COLLISION_RADIUS;
    }

    void draw(sf::RenderWindow &window) {
        // Draw game elements using the camera view
        window.setView(camera);

        // Draw map tiles
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

        // Draw the spaceship
        window.draw(spaceshipSprite);

        // Draw the hero
        window.draw(heroSprite);

        // Draw trees
        for (const auto &tree : trees) {
            window.draw(tree);
        }

        // Switch to default view for UI elements
        window.setView(window.getDefaultView());

        // Draw the health bar
        window.draw(healthBarSprite);
    }

    // Add method to create trees in initialize():
    // Update createTrees() with explicit float casting:
    void createTrees() {
        // Calculate scale to match map scale
        float treeScaleX = (TILE_SIZE * 3.0f) / TREE_WIDTH;
        float treeScaleY = (TILE_SIZE * 4.0f) / TREE_HEIGHT;

        // Create trees at various positions with explicit float casting
        const int NUM_TREES = 10; // Increased number of trees
        sf::Vector2f treePositions[NUM_TREES] = {
            {static_cast<float>((map_lowerbound_width + 5) * TILE_SIZE),
             static_cast<float>((map_lowerbound_height + 5) * TILE_SIZE)},
            {static_cast<float>((MAP_WIDTH - 8) * TILE_SIZE),
             static_cast<float>((map_lowerbound_height + 7) * TILE_SIZE)},
            {static_cast<float>((map_lowerbound_width + 10) * TILE_SIZE),
             static_cast<float>((MAP_HEIGHT - 8) * TILE_SIZE)},
            {static_cast<float>((MAP_WIDTH - 6) * TILE_SIZE), static_cast<float>((MAP_HEIGHT - 6) * TILE_SIZE)},
            {static_cast<float>((map_lowerbound_width + 15) * TILE_SIZE),
             static_cast<float>((map_lowerbound_height + 15) * TILE_SIZE)},
            {static_cast<float>((MAP_WIDTH - 12) * TILE_SIZE), static_cast<float>((MAP_HEIGHT - 12) * TILE_SIZE)},
            {static_cast<float>((map_lowerbound_width + 8) * TILE_SIZE),
             static_cast<float>((map_lowerbound_height + 12) * TILE_SIZE)},
            {static_cast<float>((MAP_WIDTH - 15) * TILE_SIZE),
             static_cast<float>((map_lowerbound_height + 10) * TILE_SIZE)},
            {static_cast<float>((map_lowerbound_width + 20) * TILE_SIZE),
             static_cast<float>((MAP_HEIGHT - 10) * TILE_SIZE)},
            {static_cast<float>((MAP_WIDTH - 10) * TILE_SIZE), static_cast<float>((MAP_HEIGHT - 15) * TILE_SIZE)}};

        // Create and setup tree sprites
        for (int i = 0; i < NUM_TREES; i++) {
            sf::Sprite treeSprite;
            treeSprite.setTexture(i % 3 == 0 ? tree : (i % 3 == 1 ? tree2 : tree3));
            treeSprite.setScale(treeScaleX, treeScaleY);
            treeSprite.setPosition(treePositions[i]);
            // Set origin to bottom center of tree for better placement
            treeSprite.setOrigin(TREE_WIDTH / 2.0f, TREE_HEIGHT);
            trees.push_back(treeSprite);
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