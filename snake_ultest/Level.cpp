#include "Level.h"

// Define the playable area boundaries
const int PLAY_AREA_LEFT = 50;
const int PLAY_AREA_RIGHT = 658;
const int PLAY_AREA_TOP = 50;
const int PLAY_AREA_BOTTOM = 466;

int currentLevel = 3; // Current level of the game

bool goInGate_progress = false;
bool goOutGate_progress = false;

bool toggleObstacleLevel3_start = false;
bool movingObstacleLevel4_start = false;

std::vector<Obstacle> obstacles; // Vector to store obstacles
std::vector<Obstacle> portals; // Vector to store portals
std::vector<Obstacle> moving_obstacles; // Vector to store moving obstacles

std::vector<Obstacle> monsters; // Vector to store monsters

std::vector<Obstacle> toggle_obstacles; // Vector to store toggle obstacles


// Function to render obstacles on the screen
void RenderObstacles(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Set obstacle color (red)
    for (const auto& obstacle : obstacles) {
        SDL_Rect obstacleRect = { obstacle.x - obstacle.w / 2, obstacle.y - obstacle.h / 2, obstacle.w, obstacle.h };
        SDL_RenderFillRect(renderer, &obstacleRect); // Render obstacle
    }
    
}

void RenderPortals(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0); // Set portals color (yellow)
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

void RenderMovingObstacles(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); // Set moving obstacles color (blue)
    for (const auto& moving_obstacle : moving_obstacles) {
		SDL_Rect obstacleRect = { moving_obstacle.x - moving_obstacle.w / 2, moving_obstacle.y - moving_obstacle.h / 2, moving_obstacle.w, moving_obstacle.h };
		SDL_RenderFillRect(renderer, &obstacleRect); // Render moving obstacles
	}
}

bool fixed1WhenPause = false;
bool fixed2WhenPause = false;
void renderMonster() {
    if (!pause) {
		fixed1WhenPause = false;
		fixed2WhenPause = false;
	}
    for (int i = 0; i < monsters.size(); i++) {
        if (fixed1WhenPause) {
            fixed2WhenPause = false;
            ApplyTexture2(g_monster1, monsters[i].x - monsters[i].w / 2, monsters[i].y - monsters[i].h / 2, monsters[i].w, monsters[i].h);
            continue;
        }
        if (fixed2WhenPause) {
            fixed1WhenPause = false;
            ApplyTexture2(g_monster2, monsters[i].x - monsters[i].w / 2, monsters[i].y - monsters[i].h / 2, monsters[i].w, monsters[i].h);
            continue;
        }
        
        if (loopCounter % 6 == 1 || loopCounter % 6 == 2 || loopCounter % 6 == 3) {
            ApplyTexture2(g_monster2, monsters[i].x - monsters[i].w / 2, monsters[i].y - monsters[i].h / 2, monsters[i].w, monsters[i].h);
            if (pause) {
                fixed2WhenPause = true;
            }
        }
        else {
            ApplyTexture2(g_monster1, monsters[i].x - monsters[i].w / 2, monsters[i].y - monsters[i].h / 2, monsters[i].w, monsters[i].h);
            if (pause) {
				fixed1WhenPause = true;
            }
        }
    }
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

void Obstacle_level_2() {
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

void Obstacle_level_4() {
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
    /*
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
    */
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

void gate_in() {
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
    AddPortal(x, y, portal_size * 3 / 2, portal_size);
}

void gate_out() {
    int x, y;
    int obstacle_size = 16;
    int portal_size = 16;

    x = PLAY_AREA_LEFT + 12;
    y = PLAY_AREA_TOP + 16 * 12;
    AddObstacle(x, y, obstacle_size * 5 / 2, obstacle_size);

    x = PLAY_AREA_LEFT + 12;
    y = PLAY_AREA_BOTTOM - 16 * 12;
    AddObstacle(x, y, obstacle_size * 5 / 2, obstacle_size);

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 13;

    SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0); // Set obstacle color (red)
    SDL_Rect obstacleRect = { x - obstacle_size / 2, y - obstacle_size / 2, obstacle_size, obstacle_size };
    SDL_RenderFillRect(g_renderer, &obstacleRect); // Render obstacle
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
        wall();

        // Avoid food - obstacle collision when first going to the current level
        do {
            foodX = rand() % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 - 2 * foodWidth - 16) + PLAY_AREA_LEFT + 8 + foodWidth;
            foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 - 2 * foodHeight - 16) + PLAY_AREA_TOP + 8 + foodHeight;
        } while (CheckCollision_food_obstacle() || CheckCollision_food_snake());

        break;
    case 2:
        // Level 2 settings
        // Set obstacle position and dimensions for level 2
        wall();
        Obstacle_level_2();
        // Avoid food - obstacle collision when first going to the current level
        do {
            foodX = rand() % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 - 2 * foodWidth - 16) + PLAY_AREA_LEFT + 8 + foodWidth;
            foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 - 2 * foodHeight - 16) + PLAY_AREA_TOP + 8 + foodHeight;
        } while (CheckCollision_food_obstacle() || CheckCollision_food_snake());

        break;
        // Add more cases for additional levels
    case 3:
        // Level 3 settings
        // Set obstacle position and dimensions for level 3
        wall();
        toggleObstacleLevel3();
        toggleObstacleLevel3_start = true;
        // Avoid food - obstacle collision when first going to the current level
        do {
            foodX = rand() % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 - 2 * foodWidth - 16) + PLAY_AREA_LEFT + 8 + foodWidth;
            foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 - 2 * foodHeight - 16) + PLAY_AREA_TOP + 8 + foodHeight;
        } while (CheckCollision_food_obstacle() || CheckCollision_food_snake());

        break;
    case 4:
        // Level 4 settings
        // Set obstacle position and dimensions for level 4
        wall();
        Obstacle_level_4();
        movingObstacleLevel4_start = true;
        // Avoid food - obstacle collision when first going to the current level
        do {
            foodX = rand() % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 - 2 * foodWidth - 16) + PLAY_AREA_LEFT + 8 + foodWidth;
            foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 - 2 * foodHeight - 16) + PLAY_AREA_TOP + 8 + foodHeight;
        } while (CheckCollision_food_obstacle() || CheckCollision_food_snake());

        break;
    default:
        // Default level settings
        // Set default obstacle position and dimensions
        wall();

        // Avoid food - obstacle collision when first going to the current level
        do {
            foodX = rand() % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 - 2 * foodWidth - 16) + PLAY_AREA_LEFT + 8 + foodWidth;
            foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 - 2 * foodHeight - 16) + PLAY_AREA_TOP + 8 + foodHeight;
        } while (CheckCollision_food_obstacle() || CheckCollision_food_snake());

        break;
    }
}

void nextLevel() {
    currentLevel++;
    reset();
}

//hitbox purple
void RenderHitbox(int x, int y, int w, int h) {
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 255, 255); // Set hitbox color (purple)
	SDL_Rect hitboxRect = { x, y, w, h };
	SDL_RenderDrawRect(g_renderer, &hitboxRect); // Render hitbox
}

void goInGate_check() {
    if (CheckCollisionWithPortals(snakeX, snakeY, 16 * 3 / 2, 16)) {
        SDL_DestroyTexture(g_snake);
        snakeX = 0; snakeY = 0;
        //lockMovement = true;
        snakeDirection = Direction::STOP;
        goInGate_progress = true;
    }

    if (tailLength > 0 && goInGate_progress) {
        for (int i = 0; i < tailLength - 1; i++) {
            if (tailX[i] < PLAY_AREA_LEFT - 8 || tailX[i] > PLAY_AREA_RIGHT + 8 || tailY[i] < PLAY_AREA_TOP - 8 || tailY[i] > PLAY_AREA_BOTTOM + 8) {
                tailShow[i] = false;
            }
        }

        if (tailX[tailLength - 1] < PLAY_AREA_LEFT - 8 || tailX[tailLength - 1] > PLAY_AREA_RIGHT + 8 || tailY[tailLength - 1] < PLAY_AREA_TOP - 8 || tailY[tailLength - 1] > PLAY_AREA_BOTTOM + 8) {
            tailShow[tailLength - 1] = false;
            goInGate_progress = false;
            nextLevel();
        }
    }
}

void goOutGate_check() {
    if (goOutGate_progress) {
        snakeX = PLAY_AREA_LEFT + 16 * 1;
        snakeY = PLAY_AREA_TOP + 16 * 13;
        g_snake = LoadTexture("2.png");
        ApplyTexture2(g_snake, snakeX - snakeWidth / 2, snakeY - snakeHeight / 2, snakeWidth, snakeHeight);

        if (tailLength > 0 && goOutGate_progress) {
            for (int i = 0; i < tailLength - 1; i++) {
                if (tailX[i] >= PLAY_AREA_LEFT - 8 || tailX[i] <= PLAY_AREA_RIGHT + 8 || tailY[i] >= PLAY_AREA_TOP - 8 || tailY[i] <= PLAY_AREA_BOTTOM + 8) {
                    tailShow[i] = true;
                    SDL_Delay(1);
                }
            }

            if (tailX[tailLength - 1] >= PLAY_AREA_LEFT - 8 || tailX[tailLength - 1] <= PLAY_AREA_RIGHT + 8 || tailY[tailLength - 1] >= PLAY_AREA_TOP - 8 || tailY[tailLength - 1] <= PLAY_AREA_BOTTOM + 8) {
                tailShow[tailLength - 1] = true;
                SDL_Delay(1);
                goOutGate_progress = false;
            }
        }
    }
}


void toggleObstacleLevel3() {
    int x, y;
    int obstacle_size = 16;

    for (y = PLAY_AREA_TOP + 16 * 2 + 8; y <= PLAY_AREA_TOP + 16 * 10 + 8; y += obstacle_size * 4) {
        for (x = PLAY_AREA_LEFT + 16 * 3 + 8; x <= PLAY_AREA_LEFT + 16 * 15 + 8; x += obstacle_size * 4) {
            toggle_obstacles.push_back({ x, y, obstacle_size * 2, obstacle_size * 2 });
        }
    }

    for (y = PLAY_AREA_TOP + 16 * 2 + 8; y <= PLAY_AREA_TOP + 16 * 10 + 8; y += obstacle_size * 4) {
        for (x = PLAY_AREA_RIGHT - 16 * 3 - 8; x >= PLAY_AREA_RIGHT - 16 * 15 - 8; x -= obstacle_size * 4) {
            toggle_obstacles.push_back({ x, y, obstacle_size * 2, obstacle_size * 2 });
        }
    }

    for (y = PLAY_AREA_BOTTOM - 16 * 2 - 8; y >= PLAY_AREA_BOTTOM - 16 * 10 - 8; y -= obstacle_size * 4) {
        for (x = PLAY_AREA_LEFT + 16 * 3 + 8; x <= PLAY_AREA_LEFT + 16 * 15 + 8; x += obstacle_size * 4) {
            toggle_obstacles.push_back({ x, y, obstacle_size * 2, obstacle_size * 2 });
        }
    }

    for (y = PLAY_AREA_BOTTOM - 16 * 2 - 8; y >= PLAY_AREA_BOTTOM - 16 * 10 - 8; y -= obstacle_size * 4) {
        for (x = PLAY_AREA_RIGHT - 16 * 3 - 8; x >= PLAY_AREA_RIGHT - 16 * 15 - 8; x -= obstacle_size * 4) {
            toggle_obstacles.push_back({ x, y, obstacle_size * 2, obstacle_size * 2 });
        }
    }
}

void RenderToggleText(const std::string& text, int x, int y) {
    SDL_Color color = { 0, 0, 0, 255 }; // Black color
    SDL_Surface* surface = TTF_RenderText_Solid(g_font, text.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_Rect destRect = { x, y, 32, 32};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(g_renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

void RenderToggleObstacles_Draw_Level3() {
    if (toggleObstacleLevel3_start) {
        loopCounter = 0;
        toggleObstacleLevel3_start = false;
    }
    if (currentLevel == 3) {
        if (loopCounter % 100 >= 0 && loopCounter % 100 <= 49) {
            for (int i = 0; i < toggle_obstacles.size(); i++) {
                if (i % 2 == 0) {
                    SDL_SetRenderDrawColor(g_renderer, 0, 0, 255, 0); // Set obstacles color (blue)
                    SDL_Rect hitboxRect = { toggle_obstacles[i].x - toggle_obstacles[i].w / 2, toggle_obstacles[i].y - toggle_obstacles[i].h / 2, toggle_obstacles[i].w, toggle_obstacles[i].h };
                    SDL_RenderDrawRect(g_renderer, &hitboxRect); // Render obstacles
                    std::string countText = std::to_string(loopCounter % 50);
                    RenderToggleText(countText, toggle_obstacles[i].x - toggle_obstacles[i].w / 2, toggle_obstacles[i].y - toggle_obstacles[i].h / 2);
                }
            }
        }
        else {
            for (int i = 0; i < toggle_obstacles.size(); i++) {
                if (i % 2 == 1) {
                    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 0); // Set obstacles color (blue)
                    SDL_Rect hitboxRect = { toggle_obstacles[i].x - toggle_obstacles[i].w / 2, toggle_obstacles[i].y - toggle_obstacles[i].h / 2, toggle_obstacles[i].w, toggle_obstacles[i].h };
                    SDL_RenderDrawRect(g_renderer, &hitboxRect); // Render obstacles
                    std::string countText = std::to_string(loopCounter % 50);
                    RenderToggleText(countText, toggle_obstacles[i].x - toggle_obstacles[i].w / 2, toggle_obstacles[i].y - toggle_obstacles[i].h / 2);
                }
            }
        }
    }
}

void RenderToggleObstacles_Fill_Level3() {
    if (toggleObstacleLevel3_start) {
        loopCounter = 0;
        toggleObstacleLevel3_start = false;
    }
    if (currentLevel == 3) {
        if (loopCounter % 100 >= 0 && loopCounter % 100 <= 49) {
            for (int i = 0; i < toggle_obstacles.size(); i++) {
                if (i % 2 == 1) {
                    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 0); // Set obstacles color (red)
                    SDL_Rect obstacleRect = { toggle_obstacles[i].x - toggle_obstacles[i].w / 2, toggle_obstacles[i].y - toggle_obstacles[i].h / 2, toggle_obstacles[i].w, toggle_obstacles[i].h };
                    SDL_RenderFillRect(g_renderer, &obstacleRect); // Render obstacles
                }
            }
        }
        else {
            for (int i = 0; i < toggle_obstacles.size(); i++) {
                if (i % 2 == 0) {

                    SDL_SetRenderDrawColor(g_renderer, 0, 0, 255, 0); // Set obstacles color (red)
                    SDL_Rect obstacleRect = { toggle_obstacles[i].x - toggle_obstacles[i].w / 2, toggle_obstacles[i].y - toggle_obstacles[i].h / 2, toggle_obstacles[i].w, toggle_obstacles[i].h };
                    SDL_RenderFillRect(g_renderer, &obstacleRect); // Render obstacles
                }
            }
        }
    }
}

bool toggleObstacleCollision() {
    if (currentLevel == 3) {
        if (loopCounter % 100 >= 0 && loopCounter % 100 <= 49) {
            for (int i = 0; i < toggle_obstacles.size(); i++) {
                if (i % 2 == 1) {
                    for (const auto& obstacle : toggle_obstacles) {
                        int distanceX = abs(snakeX - toggle_obstacles[i].x);
                        int distanceY = abs(snakeY - toggle_obstacles[i].y);
                        int edgeDistanceX = (snakeWidth + toggle_obstacles[i].w) / 2;
                        int edgeDistanceY = (snakeHeight + toggle_obstacles[i].h) / 2;

                        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
                            std::cout << "Toggle Obstacle Collision" << std::endl;
                            return true;
                        }
                    }
                }
            }
        }

        else {
            for (int i = 0; i < toggle_obstacles.size(); i++) {
                if (i % 2 == 0) {
                    for (const auto& obstacle : toggle_obstacles) {
                        int distanceX = abs(snakeX - toggle_obstacles[i].x);
                        int distanceY = abs(snakeY - toggle_obstacles[i].y);
                        int edgeDistanceX = (snakeWidth + toggle_obstacles[i].w) / 2;
                        int edgeDistanceY = (snakeHeight + toggle_obstacles[i].h) / 2;

                        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
                            std::cout << "Toggle Obstacle Collision" << std::endl;
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

void movingObstalceLevel4() {
    if (movingObstacleLevel4_start) {
        monsters.push_back({ PLAY_AREA_RIGHT - 16 * 5, PLAY_AREA_TOP + 16 * 4, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::LEFT);
        monsters.push_back({ PLAY_AREA_LEFT + 16 * 5, PLAY_AREA_BOTTOM - 16 * 4, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::RIGHT);
        /*
        monsters.push_back({ PLAY_AREA_LEFT + 16 * 19, PLAY_AREA_TOP + 16 * 4, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::LEFT);
        monsters.push_back({ PLAY_AREA_RIGHT - 16 * 19, PLAY_AREA_BOTTOM - 16 * 4, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::RIGHT);
        */
        monsters.push_back({ PLAY_AREA_LEFT + 16 * 5, PLAY_AREA_TOP + 16 * 4, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::DOWN);
        monsters.push_back({ PLAY_AREA_RIGHT - 16 * 5, PLAY_AREA_BOTTOM - 16 * 4, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::UP);
        /*
        monsters.push_back({ PLAY_AREA_LEFT + 16 * 5, PLAY_AREA_TOP + 16 * 13, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::DOWN);
        monsters.push_back({ PLAY_AREA_RIGHT - 16 * 5, PLAY_AREA_BOTTOM - 16 * 13, 16 * 3, 16 * 3 });
        moving_obstacles_direction.push_back(Direction::UP);
        */
    }
    movingObstacleLevel4_start = false;
    int moving_obstacle_speed = 16;
    if (loopCounter % 2 == 0 && !pause) {
        for (int i = 0; i < monsters.size(); i++) {
            if (currentLevel == 4) {
                switch (moving_obstacles_direction[i]) {
                case RIGHT:
                    if (monsters[i].x <= PLAY_AREA_RIGHT - 16 * 5) {
                        monsters[i].x += moving_obstacle_speed;
                    }
                    else {
                        moving_obstacles_direction[i] = UP;
                        monsters[i].y -= moving_obstacle_speed;
                    }
                    break;
                case LEFT:
                    if (monsters[i].x >= PLAY_AREA_LEFT + 16 * 5) {
                        monsters[i].x -= moving_obstacle_speed;
                    }
                    else {
                        moving_obstacles_direction[i] = DOWN;
                        monsters[i].y += moving_obstacle_speed;
                    }
                    break;
                case UP:
                    if (monsters[i].y >= PLAY_AREA_TOP + 16 * 4) {
                        monsters[i].y -= moving_obstacle_speed;
                    }
                    else {
                        moving_obstacles_direction[i] = LEFT;
                        monsters[i].x -= moving_obstacle_speed;
                    }
                    break;
                case DOWN:
                    if (monsters[i].y <= PLAY_AREA_BOTTOM - 16 * 4) {
                        monsters[i].y += moving_obstacle_speed;
                    }
                    else {
                        moving_obstacles_direction[i] = RIGHT;
                        monsters[i].x += moving_obstacle_speed;
                    }
                    break;
                }
            }
        }
    }
    if (currentLevel == 5) {
        monsters.clear();
        moving_obstacles_direction.clear();
    }
}