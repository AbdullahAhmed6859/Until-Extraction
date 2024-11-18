#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>

class TileMap {
private:
    // Core resources and texture management
    sf::Texture tilesetTexture;              // Stores the tileset image
    std::vector<sf::Sprite> mapSprites;      // Container for all map tiles
    
    // Map configuration constants
    const int TILE_SIZE = 32;                // Size of each tile in pixels
    const int MAP_WIDTH = 40;                // Number of tiles horizontally
    const int MAP_HEIGHT = 30;               // Number of tiles vertically
    const int VOID_BORDER = 5;               // Size of empty border around map
    
    // Camera settings
    sf::View camera;                         // SFML View for camera control
    float cameraSpeed = 500.0f;              // Camera movement speed (pixels/second)
    
    // Structure to define tile properties
    struct TileType {
        int x, y;                            // Coordinates in tileset
        sf::Color tint;                      // Color tint for the tile
    };
    
    // Define available tile types with their properties
    const std::vector<TileType> tiles = {
        {0, 0, sf::Color(76, 187, 23, 255)},  // Green grass - Main terrain
        {1, 0, sf::Color(187, 187, 23, 255)}, // Yellow path - Walkable paths
        {2, 0, sf::Color(0, 0, 0, 0)}         // Void tile - Transparent border
    };

public:
    // Constructor: Initialize camera with the given view size
    TileMap(const sf::Vector2f& viewSize) : camera(viewSize / 2.f, viewSize) {
        camera.setCenter(viewSize / 2.f);    // Center the camera on startup
    }

    // Initialize the tilemap and load resources
    bool initialize() {
        // Load the tileset texture from file
        if (!tilesetTexture.loadFromFile("assets/GRASS+.png")) {
            std::cout << "Failed to load tileset texture from 'assets'!" << std::endl;
            return false;
        }
        
        generateMap();                       // Create initial map layout
        return true;
    }
    
    // Generate the complete map layout
    void generateMap() {
        // Setup random number generation
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> pathChance(0, 1);
        
        // Calculate total map size including void border
        int totalWidth = MAP_WIDTH + 2 * VOID_BORDER;
        int totalHeight = MAP_HEIGHT + 2 * VOID_BORDER;
        
        // Initialize map data with void tiles
        std::vector<std::vector<int>> mapData(totalHeight, std::vector<int>(totalWidth, 2));
        
        // Create temporary array for path generation
        std::vector<std::vector<bool>> paths(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH, false));
        
        // Phase 1: Initial random path placement
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                // 20% chance for initial path placement
                if (pathChance(gen) < 0.2) {
                    paths[y][x] = true;
                }
            }
        }
        
        // Phase 2: Path smoothing using cellular automata
        for (int iteration = 0; iteration < 3; ++iteration) {
            auto newPaths = paths;
            for (int y = 0; y < MAP_HEIGHT; ++y) {
                for (int x = 0; x < MAP_WIDTH; ++x) {
                    // Count neighboring paths
                    int neighbors = 0;
                    for (int dy = -1; dy <= 1; ++dy) {
                        for (int dx = -1; dx <= 1; ++dx) {
                            int nx = x + dx;
                            int ny = y + dy;
                            if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT) {
                                if (paths[ny][nx]) neighbors++;
                            }
                        }
                    }
                    // Apply cellular automata rules
                    newPaths[y][x] = (neighbors >= 5); // Path survives/created if enough neighbors
                }
            }
            paths = newPaths;
        }
        
        // Phase 3: Transfer path data to main map
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                // Add VOID_BORDER offset when placing tiles
                mapData[y + VOID_BORDER][x + VOID_BORDER] = paths[y][x] ? 1 : 0;
            }
        }
        
        // Phase 4: Create sprites for visualization
        mapSprites.clear();  // Clear existing sprites
        for (int y = 0; y < totalHeight; ++y) {
            for (int x = 0; x < totalWidth; ++x) {
                sf::Sprite tile;
                tile.setTexture(tilesetTexture);
                
                // Get tile properties from tiles vector
                TileType selectedTile = tiles[mapData[y][x]];
                
                // Set the correct texture region for this tile
                tile.setTextureRect(sf::IntRect(
                    selectedTile.x * TILE_SIZE,
                    selectedTile.y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE
                ));
                
                // Position the tile in world space
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                tile.setColor(selectedTile.tint);  // Apply color tint
                mapSprites.push_back(tile);
            }
        }
    }
    
    // Update camera position and zoom based on input
    void updateCamera(float deltaTime, const sf::RenderWindow& window) {
        float moveSpeed = cameraSpeed * deltaTime;  // Time-based movement
        
        // Handle keyboard input for camera movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.move(-moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.move(moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            camera.move(0, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            camera.move(0, moveSpeed);
        }
        
        // Handle camera zoom
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            camera.zoom(1.0f - deltaTime);    // Zoom in
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            camera.zoom(1.0f + deltaTime);    // Zoom out
        }
    }
    
    // Draw the map to the window
    void draw(sf::RenderWindow& window) {
        window.setView(camera);              // Apply camera transformation
        for (const auto& sprite : mapSprites) {
            window.draw(sprite);             // Draw each tile
        }
    }
};

// Main program entry point
int main() {
    // Window setup
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Enhanced Grass Tilemap");
    window.setFramerateLimit(60);
    
    // Create and initialize the map
    TileMap map(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    if (!map.initialize()) {
        std::cout << "Failed to initialize the map!" << std::endl;
        system("pause");
        return 1;
    }
    
    // Clock for timing
    sf::Clock clock;
    
    // Main game loop
    while (window.isOpen()) {
        // Calculate frame time
        float deltaTime = clock.restart().asSeconds();
        
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }
        
        // Update game state
        map.updateCamera(deltaTime, window);
        
        // Render
        window.clear(sf::Color::Black);
        map.draw(window);
        window.display();
    }
    
    return 0;
}