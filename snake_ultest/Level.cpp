#include "Level.h"

// Define the playable area boundaries
const int PLAY_AREA_LEFT = 50;
const int PLAY_AREA_RIGHT = 623;
const int PLAY_AREA_TOP = 50;
const int PLAY_AREA_BOTTOM = 462;

int currentLevel = 1; // Current level of the game

std::vector<Obstacle> obstacles; // Vector to store obstacles
std::vector<Obstacle> portals; // Vector to store portals

// Function to render obstacles on the screen
void RenderObstacles(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set obstacle color (red)
    for (const auto& obstacle : obstacles) {
        SDL_Rect obstacleRect = { obstacle.x, obstacle.y, obstacle.w, obstacle.h };
        SDL_RenderFillRect(renderer, &obstacleRect); // Render obstacle
    }
}

void RenderPortals(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0); // Set portals color (blue)
    for (const auto& portal : portals) {
        SDL_Rect obstacleRect = { portal.x, portal.y, portal.w, portal.h };
        SDL_RenderFillRect(renderer, &obstacleRect); // Render portals
    }
}

// Function to check collision between the snake and obstacles
bool CheckCollisionWithObstacles(int posX, int posY, int width, int height) {
    // Calculate the distance between the snake's head and the food
    for (const auto& obstacle : obstacles) {
        int distanceX = abs(posX - obstacle.x);
        int distanceY = abs(posY - obstacle.y);

        // If the snake's head is close enough to the food, consider it a collision
        if (distanceX < width * 1 && distanceY < height * 1) {
            return true;
        }
    }
    return false;
}

bool CheckCollisionWithPortals(int posX, int posY, int width, int height) {
    for (const auto& portal : portals) {
        int distanceX = abs(posX - portal.x);
        int distanceY = abs(posY - portal.y);

        if (distanceX < width && distanceY < height) {
            return true;
        }
    }
    return false;
}

void AddObstacle(int x, int y, int w, int h) {
    Obstacle obstacle = { x, y , w, h };
    obstacles.push_back(obstacle);
}

void AddPortal(int x, int y, int w, int h) {
    Obstacle portal = { x, y , w, h };
    portals.push_back(portal);
}

void RemoveObstacle(int x, int y) {
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
        if (it->x == x && it->y == y) {
            obstacles.erase(it);
            break;
        }
    }
}

void Obstacle_level_1() {
    int x, y;
    int obstacle_size = 10;
    y = (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4 + PLAY_AREA_TOP;
    for (x = PLAY_AREA_LEFT + 80; x <= (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8 + PLAY_AREA_LEFT; x ++) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }

    x = (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8 + PLAY_AREA_LEFT;
    for (y = PLAY_AREA_TOP + 20; y <= (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4 + PLAY_AREA_TOP; y ++) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }

    y = (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4 + PLAY_AREA_TOP;
    for (x = PLAY_AREA_RIGHT - 80; x >= PLAY_AREA_RIGHT - (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8; x --) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }

    x = PLAY_AREA_RIGHT - (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8;
    for (y = PLAY_AREA_TOP + 20; y <= (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4 + PLAY_AREA_TOP; y ++) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }

    y = PLAY_AREA_BOTTOM - (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4;
    for (x = PLAY_AREA_LEFT + 80; x <= (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8 + PLAY_AREA_LEFT; x ++) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }

    x = (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8 + PLAY_AREA_LEFT;
    for (y = PLAY_AREA_BOTTOM - 20; y >= PLAY_AREA_BOTTOM - (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4; y --) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }

    y = PLAY_AREA_BOTTOM - (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4;
    for (x = PLAY_AREA_RIGHT - 80; x >= PLAY_AREA_RIGHT - (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8; x --) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }

    x = PLAY_AREA_RIGHT - (PLAY_AREA_RIGHT - PLAY_AREA_LEFT) * 3 / 8;
    for (y = PLAY_AREA_BOTTOM - 20; y >= PLAY_AREA_BOTTOM - (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 4; y --) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }
}

void Obstacle_level_2() {
    // Define the center of the play area
    int centerX = (PLAY_AREA_RIGHT + PLAY_AREA_LEFT) / 2;
    int centerY = (PLAY_AREA_BOTTOM + PLAY_AREA_TOP) / 2 + 15;
    int obstacle_size = 10;
    // Define the length of the X arms (adjust as needed)
    int armLength = 140;

    // Add obstacles for the diagonal arms of the X
    for (int i = -armLength; i <= armLength; ++i) {
        if (i != 0) { // Skip the center position
            AddObstacle((centerX + i) * 1, (centerY + i) * 1, obstacle_size, obstacle_size);
            AddObstacle((centerX + i) * 1, (centerY - i) * 1, obstacle_size, obstacle_size);
        }
    }

    int obstacleWidth = 10; // Adjust as needed
    int obstacleHeight = 10; // Adjust as needed

    // Calculate the center coordinates of each edge
    int topEdgeCenterX = (PLAY_AREA_RIGHT + PLAY_AREA_LEFT) / 2;
    int topEdgeCenterY = PLAY_AREA_TOP + (obstacleHeight / 2) + 10; // Adjust for spacing from top edge
    int bottomEdgeCenterX = (PLAY_AREA_RIGHT + PLAY_AREA_LEFT) / 2;
    int bottomEdgeCenterY = PLAY_AREA_BOTTOM - (obstacleHeight / 2) - 10; // Adjust for spacing from bottom edge

    // Add obstacles for the four squares
    AddObstacle(topEdgeCenterX, topEdgeCenterY, obstacleWidth, obstacleHeight);
    AddObstacle(bottomEdgeCenterX, bottomEdgeCenterY, obstacleWidth, obstacleHeight);
}

void Obstacle_level_3() {
    // Define the width and height of the obstacles
    int obstacleWidth = 10; // Adjust as needed
    int obstacleHeight = 10; // Adjust as needed

    // Define the offset for obstacles
    int offsetX = 100; // Adjust as needed
    int offsetY = 90; // Adjust as needed

    // Iterate over the play area and add obstacles with offset
    for (int y = PLAY_AREA_TOP + offsetY; y < PLAY_AREA_BOTTOM - obstacleHeight; y += offsetY + obstacleHeight) {
        for (int x = PLAY_AREA_LEFT + offsetX; x < PLAY_AREA_RIGHT - obstacleWidth; x += offsetX + obstacleWidth) {
            AddObstacle(x, y, obstacleWidth, obstacleHeight);
        }
    }
}

void gate() {
    // Define gate properties
    const int gateWidth = 80; // Adjust as needed
    const int gateHeight = 100; // Adjust as needed
    const int gateX = PLAY_AREA_LEFT; // Center the gate horizontally
    const int gateY = (PLAY_AREA_BOTTOM - PLAY_AREA_TOP) / 2 + PLAY_AREA_TOP; // Center the gate vertically


    int y = gateY - gateHeight / 2;
    for (int x = gateX; x < gateX + gateWidth; x += 20) {
        AddObstacle(x, y, 20, 20);
    }

    y = gateY + gateHeight / 2;
    for (int x = gateX; x < gateX + gateWidth; x += 20) {
        AddObstacle(x, y, 20, 20);
    }

    int x = gateX;
    for (int y = gateY - gateHeight / 2 + 20; y <= gateY + gateHeight / 2 - 20; y += 20) {
        AddPortal(x, y, 20, 20);
    }
}

void Level(int levelNumber) {
    // Adjust game parameters based on the level number
    switch (levelNumber) {
    case 1:
        // Level 1 settings
        // Set obstacle position and dimensions for level 1
        SNAKE_SPEED = 20;
        Obstacle_level_1();
        break;
    case 2:
        // Level 2 settings
        // Set obstacle position and dimensions for level 2
        SNAKE_SPEED = 25;
        Obstacle_level_2();
        break;
        // Add more cases for additional levels
    case 3:
        // Level 3 settings
        // Set obstacle position and dimensions for level 3
        SNAKE_SPEED = 30;
        Obstacle_level_3();
        break;
    default:
        // Default level settings
        // Set default obstacle position and dimensions

        break;
    }
}
void nextLevel() {
    reset();
    currentLevel++;
    Level(currentLevel);
    g_food = LoadTexture("Food.png");
    ApplyTexture2(g_food, foodX, foodY, foodWidth * 2, foodHeight * 2);
}