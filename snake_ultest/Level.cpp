#include "Level.h"

// Define the playable area boundaries
const int PLAY_AREA_LEFT = 50;
const int PLAY_AREA_RIGHT = 658;
const int PLAY_AREA_TOP = 50;
const int PLAY_AREA_BOTTOM = 466;

int currentLevel = 1; // Current level of the game

std::vector<Obstacle> obstacles; // Vector to store obstacles
std::vector<Obstacle> portals; // Vector to store portals

// Function to render obstacles on the screen
void RenderObstacles(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Set obstacle color (red)
    for (const auto& obstacle : obstacles) {
        SDL_Rect obstacleRect = { obstacle.x - obstacle.w / 2, obstacle.y - obstacle.h / 2, obstacle.w, obstacle.h };
        SDL_RenderFillRect(renderer, &obstacleRect); // Render obstacle
    }
    
}

void RenderPortals(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0); // Set portals color (blue)
    for (const auto& portal : portals) {
        SDL_Rect obstacleRect = { portal.x - portal.w / 2, portal.y - portal.h / 2, portal.w, portal.h };
        SDL_RenderFillRect(renderer, &obstacleRect); // Render portals
    }
}

void RenderHitbox(SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set hitbox color (green)
	SDL_Rect hitboxRect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &hitboxRect); // Render hitbox
}

// Function to check collision between the snake and obstacles
bool CheckCollisionWithObstacles(int posX, int posY, int width, int height) {
    // Calculate the distance between the snake's head and the food
    for (const auto& obstacle : obstacles) {
        int distanceX = abs(posX - obstacle.x);
        int distanceY = abs(posY - obstacle.y);
        int edgeDistanceX = snakeWidth / 2 + obstacle.w / 2;
        int edgeDistanceY = snakeHeight / 2 + obstacle.h / 2;

        // If the snake's head is close enough to the food, consider it a collision
        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
            std::cout << "Collision with obstacle at (" << obstacle.x << ", " << obstacle.y << ")" << std::endl;
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
    int obstacle_size = 16;
    
    y = PLAY_AREA_TOP + 16 * 9;
    for (x = PLAY_AREA_LEFT + 16 * 5; x <= PLAY_AREA_LEFT + 16 * 16; x += obstacle_size) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }
    for (x = PLAY_AREA_LEFT + 16 * 22; x <= PLAY_AREA_LEFT + 16 * 33; x += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
    }
    y = PLAY_AREA_TOP + 16 * 17;
    for (x = PLAY_AREA_LEFT + 16 * 5; x <= PLAY_AREA_LEFT + 16 * 16; x += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}
    for (x = PLAY_AREA_LEFT + 16 * 22; x <= PLAY_AREA_LEFT + 16 * 33; x += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}

	x = PLAY_AREA_LEFT + 16 * 16;
    for (y = PLAY_AREA_TOP + 16 * 3; y <= PLAY_AREA_TOP + 16 * 9; y += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}
    for (y = PLAY_AREA_TOP + 16 * 17; y <= PLAY_AREA_TOP + 16 * 23; y += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}

    x = PLAY_AREA_LEFT + 16 * 22;
    for (y = PLAY_AREA_TOP + 16 * 3; y <= PLAY_AREA_TOP + 16 * 9; y += obstacle_size) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }
    for (y = PLAY_AREA_TOP + 16 * 17; y <= PLAY_AREA_TOP + 16 * 23; y += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}
    
}

void Obstacle_level_2() {
    int x, y;
    int n = 9, m = 11;
    int obstacle_size = 16;

    y = PLAY_AREA_TOP + 16 * 3;
    for (x = PLAY_AREA_LEFT + 16 * 9; x <= PLAY_AREA_LEFT + 16 * 10; x += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}
    n = 9, m = 11;
    for (int i = 4; i <= 13; i++) {
        for (int j = n; j <= m; j++) {
            AddObstacle(PLAY_AREA_LEFT + 16 * j, PLAY_AREA_TOP + 16 * i, obstacle_size, obstacle_size);
        }
        n++;
        m++;
    }

    y = PLAY_AREA_TOP + 16 * 3;
    for (x = PLAY_AREA_RIGHT - 16 * 9; x >= PLAY_AREA_RIGHT - 16 * 10; x -= obstacle_size) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }
    n = 9, m = 11;
    for (int i = 4; i <= 13; i++) {
        for (int j = n; j <= m; j++) {
            AddObstacle(PLAY_AREA_RIGHT - 16 * j, PLAY_AREA_TOP + 16 * i, obstacle_size, obstacle_size);
        }
        n++;
        m++;
    }

    y = PLAY_AREA_BOTTOM - 16 * 3;
    for (x = PLAY_AREA_LEFT + 16 * 9; x <= PLAY_AREA_LEFT + 16 * 10; x += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}
    n = 9, m = 11;
    for (int i = 4; i <= 13; i++) {
        for (int j = n; j <= m; j++) {
			AddObstacle(PLAY_AREA_LEFT + 16 * j, PLAY_AREA_BOTTOM - 16 * i, obstacle_size, obstacle_size);
		}
		n++;
		m++;
	}

    y = PLAY_AREA_BOTTOM - 16 * 3;
    for (x = PLAY_AREA_RIGHT - 16 * 9; x >= PLAY_AREA_RIGHT - 16 * 10; x -= obstacle_size) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }
    n = 9, m = 11;
    for (int i = 4; i <= 13; i++) {
        for (int j = n; j <= m; j++) {
			AddObstacle(PLAY_AREA_RIGHT - 16 * j, PLAY_AREA_BOTTOM - 16 * i, obstacle_size, obstacle_size);
		}
		n++;
		m++;
	}

    x = PLAY_AREA_LEFT + 16 * 18;
    y = PLAY_AREA_TOP + 16 * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
			AddObstacle(x + j * 16, y + i * 16, obstacle_size, obstacle_size);
		}
	}

    x = PLAY_AREA_RIGHT - 16 * 18;
    y = PLAY_AREA_BOTTOM - 16 * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            AddObstacle(x - j * 16, y - i * 16, obstacle_size, obstacle_size);
        }
    }

    x = PLAY_AREA_LEFT + 16 * 9;
    y = PLAY_AREA_TOP + 16 * 12;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            AddObstacle(x + j * 16, y + i * 16, obstacle_size, obstacle_size);
        }
    }

    x = PLAY_AREA_RIGHT - 16 * 9;
    y = PLAY_AREA_BOTTOM - 16 * 12;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
			AddObstacle(x - j * 16, y - i * 16, obstacle_size, obstacle_size);
		}
	}
}

void Obstacle_level_3() {
    int x, y;
    int obstacle_size = 16;
    
    for (y = PLAY_AREA_TOP + 16 * 2 + 8; y <= PLAY_AREA_TOP + 16 * 10 + 8; y += obstacle_size * 4) {
        for (x = PLAY_AREA_LEFT + 16 * 3 + 8; x <= PLAY_AREA_LEFT + 16 * 15 + 8; x += obstacle_size * 4) {
            AddObstacle(x, y, obstacle_size * 2, obstacle_size * 2);
        }
    }

    for (y = PLAY_AREA_TOP + 16 * 2 + 8; y <= PLAY_AREA_TOP + 16 * 10 + 8; y += obstacle_size * 4) {
        for (x = PLAY_AREA_RIGHT - 16 * 3 - 8; x >= PLAY_AREA_RIGHT - 16 * 15 - 8; x -= obstacle_size * 4) {
			AddObstacle(x, y, obstacle_size * 2, obstacle_size * 2);
		}
	}

    for (y = PLAY_AREA_BOTTOM - 16 * 2 - 8; y >= PLAY_AREA_BOTTOM - 16 * 10 - 8; y -= obstacle_size * 4) {
        for (x = PLAY_AREA_LEFT + 16 * 3 + 8; x <= PLAY_AREA_LEFT + 16 * 15 + 8; x += obstacle_size * 4) {
            AddObstacle(x, y, obstacle_size * 2, obstacle_size * 2);
        }
    }

    for (y = PLAY_AREA_BOTTOM - 16 * 2 - 8; y >= PLAY_AREA_BOTTOM - 16 * 10 - 8; y -= obstacle_size * 4) {
        for (x = PLAY_AREA_RIGHT - 16 * 3 - 8; x >= PLAY_AREA_RIGHT - 16 * 15 - 8; x -= obstacle_size * 4) {
			AddObstacle(x, y, obstacle_size * 2, obstacle_size * 2);
		}
	}
}

void gate() {
    int x, y;
    int obstacle_size = 16;
    int portal_size = 16;

    x = PLAY_AREA_RIGHT - 12;
    y = PLAY_AREA_TOP + 16 * 12;
    AddObstacle(x, y, obstacle_size * 5 / 2, obstacle_size);

    x = PLAY_AREA_RIGHT - 12;
    y = PLAY_AREA_BOTTOM - 16 * 12;
    AddObstacle(x, y, obstacle_size * 5 / 2, obstacle_size);

    x = PLAY_AREA_RIGHT - 4;
    y = PLAY_AREA_TOP + 16 * 13;
    AddPortal(x, y, portal_size * 5 / 4, portal_size);
}

void wall() {
    int top = PLAY_AREA_TOP;
    int bottom = PLAY_AREA_BOTTOM;
    int left = PLAY_AREA_LEFT;
    int right = PLAY_AREA_RIGHT;

    int x, y;

    for (x = left; x <= right; x++) {
        AddObstacle(x, top, 16, 16);
		AddObstacle(x, bottom, 16, 16);
    }

    for (y = top; y <= bottom; y++) {
		AddObstacle(left, y, 16, 16);
        AddObstacle(right, y, 16, 16);
    }
}

void Level(int levelNumber) {
    // Adjust game parameters based on the level number
    switch (levelNumber) {
    case 1:
        // Level 1 settings
        // Set obstacle position and dimensions for level 1
        SNAKE_SPEED = 16;
        wall();
        Obstacle_level_1();
        break;
    case 2:
        // Level 2 settings
        // Set obstacle position and dimensions for level 2
        SNAKE_SPEED = 16;
        wall();
        Obstacle_level_2();
        break;
        // Add more cases for additional levels
    case 3:
        // Level 3 settings
        // Set obstacle position and dimensions for level 3
        SNAKE_SPEED = 32;
        wall();
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
    ApplyTexture2(g_food, foodX - foodWidth / 2, foodY - foodHeight / 2, foodWidth, foodHeight);
}

//hitbox purple
void RenderHitbox(int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 255, 255); // Set hitbox color (purple)
	SDL_Rect hitboxRect = { x, y, w, h };
	SDL_RenderDrawRect(g_renderer, &hitboxRect); // Render hitbox
}