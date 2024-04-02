#include "Level.h"

// Define the playable area boundaries
const int PLAY_AREA_LEFT = 50;
const int PLAY_AREA_RIGHT = 658;
const int PLAY_AREA_TOP = 50;
const int PLAY_AREA_BOTTOM = 466;

int currentLevel = 4; // Current level of the game

bool goInGate_progress = false;
bool goOutGate_progress = false;

bool toggleObstacleLevel3_start = false;
bool movingObstacleLevel4_start = false;

std::vector<Obstacle> obstacles; // Vector to store obstacles
std::vector<Obstacle> portals; // Vector to store portals
std::vector<Obstacle> moving_obstacles; // Vector to store moving obstacles

std::vector<Obstacle> monsters; // Vector to store monsters

std::vector<Obstacle> toggle_obstacles; // Vector to store toggle obstacles

std::vector<subPortal> subPortals; // Vector to store subPortals


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

void setColor_code(int color_num) {
    switch (color_num) {
    case 1:
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 0); // Set obstacle color (red)
        break;
    case 2:
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 0); // Set obstacle color (green)
        break;
    case 3:
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 255, 0); // Set obstacle color (blue)
        break;
    case 4:
        SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0); // Set obstacle color (yellow)
        break;
    case 5:
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 255, 0); // Set obstacle color (purple)
        break;
    case 6:
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, 0); // Set obstacle color (cyan)
        break;
    case 7:
        SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 0); // Set obstacle color (white)
        break;
    case 8:
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0); // Set obstacle color (black)
        break;
    case 9:
        SDL_SetRenderDrawColor(g_renderer, 255, 165, 0, 0); // Set obstacle color (orange)
		break;
    case 10: // light green
        SDL_SetRenderDrawColor(g_renderer, 144, 238, 144, 0); // Set obstacle color (light green)
		break;
    default:
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 0); // Set obstacle color (red)
        break;

    }
}

void RenderSubPortal(SDL_Renderer* renderer) {
    for (const auto& subportal : subPortals) {
        setColor_code(subportal.color_code);
        SDL_Rect inRect = { subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h };
        SDL_RenderFillRect(renderer, &inRect); // Render subPortal in
        SDL_Rect outRect = { subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h };
        SDL_RenderFillRect(renderer, &outRect); // Render subPortal out
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

    x = PLAY_AREA_RIGHT - 16 * 1 - 8;
    y = PLAY_AREA_TOP + 16 * 12;
    AddObstacle(x, y, obstacle_size * 2, obstacle_size);

    x = PLAY_AREA_RIGHT - 16 * 1 - 8;
    y = PLAY_AREA_BOTTOM - 16 * 12;
    AddObstacle(x, y, obstacle_size * 2, obstacle_size);

    x = PLAY_AREA_RIGHT - 4;
    y = PLAY_AREA_TOP + 16 * 13;
    AddPortal(x, y, portal_size * 3 / 2, portal_size);
}

std::vector<bool> gate_open_step = { 1, 0, 0, 0 };

void gate_out1() {
    int x, y;

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 13;
    AddObstacle(x, y, 16, 16 * 3);
}

void gate_out2() {
    int x, y;
    x = PLAY_AREA_LEFT + 16 * 2;
    y = PLAY_AREA_TOP + 16 * 13;
    AddObstacle(x, y, 16, 16 * 3);

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 12;
    for (int i = 0; i <= 1; i++) {
        AddObstacle(x, y + 16 * (2 * i), 16, 16);
    }

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 13;
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0);
    SDL_Rect obstacleRect = { x, y, 16, 16 };
    SDL_RenderFillRect(g_renderer, &obstacleRect);
}

void gate_out3() {
    int x, y;
    x = PLAY_AREA_LEFT + 16 * 2;
    y = PLAY_AREA_TOP + 16 * 12;
    for (int i = 0; i <= 1; i++) {
        AddObstacle(x, y + 16 * (2 * i), 16, 16);
    }

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 12;
    for (int i = 0; i <= 1; i++) {
        AddObstacle(x, y + 16 * (2 * i), 16, 16);
    }

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 13;
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0);
    SDL_Rect obstacleRect = { x, y, 16, 16 };
    SDL_RenderFillRect(g_renderer, &obstacleRect);
}

void gate_out4() {
    int x, y;
    int obstacle_size = 16;
    int portal_size = 16;

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 12;
    AddObstacle(x, y, obstacle_size, obstacle_size);

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_BOTTOM - 16 * 12;
    AddObstacle(x, y, obstacle_size, obstacle_size);

    x = PLAY_AREA_LEFT + 16 * 1;
    y = PLAY_AREA_TOP + 16 * 13;

    SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0);
    SDL_Rect obstacleRect = { x - obstacle_size / 2, y - obstacle_size / 2, obstacle_size, obstacle_size };
    SDL_RenderFillRect(g_renderer, &obstacleRect);
}

void gate_open() {
    if (gate_open_step[0]) {
        gate_out1();
        gate_open_step[0] = false;
        gate_open_step[1] = true;
        return;
    }
    if (gate_open_step[1]) {
        obstacles.clear();
        subPortals.clear();
        Level(currentLevel);
		gate_out2();
		gate_open_step[1] = false;
		gate_open_step[2] = true;
        return;
	}
    if (gate_open_step[2]) {
        obstacles.clear();
        subPortals.clear();
        Level(currentLevel);
		gate_out3();
		gate_open_step[2] = false;
		gate_open_step[3] = true;
        lockMovement = false;
        return;
	}
    if (gate_open_step[3]) {
        obstacles.clear();
        subPortals.clear();
        Level(currentLevel);
		gate_out4();
        spawnFood();
        gate_open_step[3] = false;
	}
}

void fake_portal_gate() {
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 0);
    SDL_Rect obstacleRect = { PLAY_AREA_LEFT + 16 * 1 - 16 / 2, PLAY_AREA_TOP + 16 * 13 - 16 / 2, 16, 16 };
    SDL_RenderFillRect(g_renderer, &obstacleRect);
}

bool gate_open_done = false;
bool isMovingMonster = false;



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

        break;
    case 2:
        // Level 2 settings
        // Set obstacle position and dimensions for level 2
        wall();
        Obstacle_level_2();


        break;
        // Add more cases for additional levels
    case 3:
        // Level 3 settings
        // Set obstacle position and dimensions for level 3
        wall();
        toggleObstacleLevel3();
        toggleObstacleLevel3_start = true;


        break;
    case 4:
        // Level 4 settings
        // Set obstacle position and dimensions for level 4
        wall();
        Obstacle_level_4();
        movingObstacleLevel4_start = true;


        break;
    case 5:
        wall();
        subPortalLevel5();

        break;

    default:
        // Default level settings
        // Set default obstacle position and dimensions
        wall();

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
        lockMovement = true;
        goInGate_progress = true;
        SDL_DestroyTexture(g_snake);
        MoveSnake(running);
        snakeX = 0; snakeY = 0;
    }

    if (tailLength > 0 && goInGate_progress) {

        for (int i = 0; i < tailLength - 1; i++) {
            if (tailX[i] < PLAY_AREA_LEFT - 8 || tailX[i] > PLAY_AREA_RIGHT + 8 || tailY[i] < PLAY_AREA_TOP - 8 || tailY[i] > PLAY_AREA_BOTTOM + 8) {
                tailShow[i] = false;
            }
        }

        if (tailX[tailX.size() - 1] < PLAY_AREA_LEFT - 8 || tailX[tailX.size() - 1] > PLAY_AREA_RIGHT + 8 || tailY[tailX.size() - 1] < PLAY_AREA_TOP - 8 || tailY[tailX.size() - 1] > PLAY_AREA_BOTTOM + 8) {
            tailShow[tailX.size() - 1] = false;
            goInGate_progress = false;
            nextLevel();
        }
    }
}

void goOutGate_check() {
    if (gate_open_done) {
        obstacles.clear();
        subPortals.clear();
        if (currentLevel == 4) isMovingMonster = true;
        Level(currentLevel);
        gate_open_done = false;
    }
    if (goOutGate_progress) {
        if (gate_open_step[0]) {
            SDL_DestroyTexture(g_snake);
            snakeX = 0;
            snakeY = 0;

            return;
        }
        snakeX = PLAY_AREA_LEFT + 16 * 2;
        snakeY = PLAY_AREA_TOP + 16 * 13;
        g_snake = LoadTexture("2.png");
        ApplyTexture2(g_snake, snakeX - snakeWidth / 2, snakeY - snakeHeight / 2, snakeWidth, snakeHeight);

        lockMovement = false;
		

        if (tailLength > 0 && goOutGate_progress) {
            for (int i = 0; i < tailLength - 1; i++) {
                if (tailX[i] >= PLAY_AREA_LEFT - 8 || tailX[i] <= PLAY_AREA_RIGHT + 8 || tailY[i] >= PLAY_AREA_TOP - 8 || tailY[i] <= PLAY_AREA_BOTTOM + 8) {
                    tailShow[i] = true;
                    SDL_Delay(1);
                }
            }

            if (tailX[tailX.size() - 1] >= PLAY_AREA_LEFT - 8 || tailX[tailX.size() - 1] <= PLAY_AREA_RIGHT + 8 || tailY[tailX.size() - 1] >= PLAY_AREA_TOP - 8 || tailY[tailX.size() - 1] <= PLAY_AREA_BOTTOM + 8) {
                tailShow[tailX.size() - 1] = true;
                SDL_Delay(1);
                gate_open_done = true;
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
                    std::string countText;
                    if (loopCounter % 50 >= 1 && loopCounter % 50 <= 10) {
                        countText = "0" + std::to_string(loopCounter % 50);
                    }
                    else {
                        countText = std::to_string(loopCounter % 50);
                    }
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
                    std::string countText;
                    if (loopCounter % 50 >= 1 && loopCounter % 50 <= 10) {
                        countText = "0" + std::to_string(loopCounter % 50);
                    }
                    else {
                        countText = std::to_string(loopCounter % 50);
                    }
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
    if (isMovingMonster) {
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
    }
    
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

void snakeTeleport_in_to_out() {
    for (const auto& subportal : subPortals) {
        int distanceX = abs(snakeX - subportal.in.x);
        int distanceY = abs(snakeY - subportal.in.y);
        int edgeDistanceX = (snakeWidth + subportal.in.w) / 2;
        int edgeDistanceY = (snakeHeight + subportal.in.h) / 2;
        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
            if (subportal.parallel) {
                switch (snakeDirection) {
                case UP:
                    snakeX = subportal.out.x;
                    snakeY = subportal.out.y - 16;
                    break;
                case DOWN:
                    snakeX = subportal.out.x;
                    snakeY = subportal.out.y + 16;
                    break;
                case LEFT:
                    snakeX = subportal.out.x - 16;
                    snakeY = subportal.out.y;
                    break;
                case RIGHT:
                    snakeX = subportal.out.x + 16;
                    snakeY = subportal.out.y;
                    break;
                }
            }
            else {

                switch (snakeDirection) {
                case UP:
                    lastDirection = DOWN;
                    snakeDirection = DOWN;
                    snakeX = subportal.out.x;
                    snakeY = subportal.out.y + 16;
                    break;
                case DOWN:
                    lastDirection = UP;
                    snakeDirection = UP;
                    snakeX = subportal.out.x;
                    snakeY = subportal.out.y - 16;
                    break;
                case LEFT:
                    lastDirection = RIGHT;
                    snakeDirection = RIGHT;
                    snakeX = subportal.out.x + 16;
                    snakeY = subportal.out.y;
                    break;
                case RIGHT:
                    lastDirection = LEFT;
                    snakeDirection = LEFT;
                    snakeX = subportal.out.x - 16;
                    snakeY = subportal.out.y;
                    break;
                }

            }
        }
    }
}

void snakeTeleport_out_to_in() {
    for (const auto& subportal : subPortals) {
        int distanceX = abs(snakeX - subportal.out.x);
        int distanceY = abs(snakeY - subportal.out.y);
        int edgeDistanceX = (snakeWidth + subportal.out.w) / 2;
        int edgeDistanceY = (snakeHeight + subportal.out.h) / 2;
        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
            if (subportal.parallel) {
                switch (snakeDirection) {
                case UP:
                    snakeX = subportal.in.x;
                    snakeY = subportal.in.y - 16;
                    break;
                case DOWN:
                    snakeX = subportal.in.x;
                    snakeY = subportal.in.y + 16;
                    break;
                case LEFT:
                    snakeX = subportal.in.x - 16;
                    snakeY = subportal.in.y;
                    break;
                case RIGHT:
                    snakeX = subportal.in.x + 16;
                    snakeY = subportal.in.y;
                    break;
                }
            }
            else {
                switch (snakeDirection) {
				case UP:
                    lastDirection = DOWN;
					snakeDirection = DOWN;
					snakeX = subportal.in.x;
					snakeY = subportal.in.y + 16;
					break;
				case DOWN:
                    lastDirection = UP;
					snakeDirection = UP;
					snakeX = subportal.in.x;
					snakeY = subportal.in.y - 16;
					break;
				case LEFT:
                    lastDirection = RIGHT;
					snakeDirection = RIGHT;
					snakeX = subportal.in.x + 16;
					snakeY = subportal.in.y;
					break;
				case RIGHT:
                    lastDirection = LEFT;
					snakeDirection = LEFT;
					snakeX = subportal.in.x - 16;
					snakeY = subportal.in.y;
					break;
				}
            }
        }
    }
}

void subPortalLevel5() {
    // Obstacle setup
    // Top Left field
    for (int i = 0; i <= 9; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * (1 + i), PLAY_AREA_TOP + 16 * 1, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (1 + i), PLAY_AREA_TOP + 16 * 17, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (1 + i), PLAY_AREA_TOP + 16 * 18, 16, 16);
    }

    for (int i = 0; i <= 15; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * 1, PLAY_AREA_TOP + 16 * (2 + i), 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * 10, PLAY_AREA_TOP + 16 * (2 + i), 16, 16);
    }

    // Top middle field
    for (int i = 0; i <= 9; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * (11 + i), PLAY_AREA_TOP + 16 * 1, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (11 + i), PLAY_AREA_TOP + 16 * 12, 16, 16);
    }

    for (int i = 0; i <= 9; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * 11, PLAY_AREA_TOP + 16 * (2 + i), 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (2 + i), 16, 16);
    }

    // Top right field
    for (int i = 0; i <= 8; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * (21 + i), PLAY_AREA_TOP + 16 * 1, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (29 + i), PLAY_AREA_TOP + 16 * 11, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (29 + i), PLAY_AREA_TOP + 16 * 3, 16, 16);
    }
    AddObstacle(PLAY_AREA_LEFT + 16 * 29, PLAY_AREA_TOP + 16 * 2, 16, 16);

    for (int i = 0; i <= 16; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * (21 + i), PLAY_AREA_TOP + 16 * 12, 16, 16);
    }

    for (int i = 0; i <= 6; i++) {
        AddObstacle(PLAY_AREA_RIGHT - 16 * 1, PLAY_AREA_TOP + 16 * (4 + i), 16, 16);
    }

    // Fill between top right and upmost wall
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 1; j++) {
            AddObstacle(PLAY_AREA_RIGHT - 16 * (1 + i), PLAY_AREA_TOP + 16 * (1 + j), 16, 16);
        }
	}
    
    // Bottom Middle field
    for (int i = 0; i <= 17; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * (11 + i), PLAY_AREA_BOTTOM - 16 * 1, 16, 16);
		AddObstacle(PLAY_AREA_LEFT + 16 * (11 + i), PLAY_AREA_BOTTOM - 16 * 13, 16, 16);
    }

    for (int i = 0; i <= 10; i++) {
		AddObstacle(PLAY_AREA_LEFT + 16 * 11, PLAY_AREA_BOTTOM - 16 * (2 + i), 16, 16);
		AddObstacle(PLAY_AREA_LEFT + 16 * 28, PLAY_AREA_BOTTOM - 16 * (2 + i), 16, 16);
	}

    AddObstacle(PLAY_AREA_RIGHT - 16 * 11, PLAY_AREA_BOTTOM - 16 * 3, 16, 16);

    // Bottom right field
    for (int i = 0; i <= 12; i++) {
        AddObstacle(PLAY_AREA_RIGHT - 16 * 9, PLAY_AREA_BOTTOM - 16 * (1 + i), 16, 16);
    }

    for (int i = 0; i <= 7; i++) {
        AddObstacle(PLAY_AREA_RIGHT - 16 * (1 + i), PLAY_AREA_BOTTOM - 16 * 1, 16, 16);
    }

    for (int i = 0; i <= 5; i++) {
        AddObstacle(PLAY_AREA_RIGHT - 16 * (3 + i), PLAY_AREA_BOTTOM - 16 * 3, 16, 16);
        AddObstacle(PLAY_AREA_RIGHT - 16 * (1 + i), PLAY_AREA_BOTTOM - 16 * 6, 16, 16);
        AddObstacle(PLAY_AREA_RIGHT - 16 * (3 + i), PLAY_AREA_BOTTOM - 16 * 9, 16, 16);
        AddObstacle(PLAY_AREA_RIGHT - 16 * (1 + i), PLAY_AREA_BOTTOM - 16 * 12, 16, 16);

    }

    //...

    // Portal setup
    for (int i = 0; i <= 3; i++) {
        RemoveObstacle(PLAY_AREA_LEFT + 16 * (4 + i), PLAY_AREA_TOP + 16);
        RemoveObstacle(PLAY_AREA_LEFT + 16 * (14 + i), PLAY_AREA_TOP + 16 * 1);

        subPortals.push_back({
            {PLAY_AREA_LEFT + 16 * (4 + i), PLAY_AREA_TOP + 16, 16, 16},
            {PLAY_AREA_LEFT + 16 * (14 + i), PLAY_AREA_TOP + 16 * 1, 16, 16},
            3, // Color: Blue
            0 // No Parallel
            });
    }

    for (int i = 0; i <= 2; i++) {
        RemoveObstacle(PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (3 + i));
        RemoveObstacle(PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (8+ i));

        subPortals.push_back({
            {PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (3 + i), 16, 16},
            {PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (8 + i), 16, 16},
            2, // Color: Green
            1 // Parallel
            });
    }

    subPortals.push_back({
        {PLAY_AREA_RIGHT - 16 * 7, PLAY_AREA_TOP + 16 * 7, 16, 16},
        {PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * 19, 16, 16},
        6, // Color: Cyan
        1 // Parallel
        });

    for (int i = 0; i <= 2; i++) {
        subPortals.push_back({
            {PLAY_AREA_LEFT + 16 * (23 + i), PLAY_AREA_TOP + 16 * 13, 16, 16},
            {PLAY_AREA_LEFT + 16 * (6 + i), PLAY_AREA_BOTTOM - 16 * 8, 16, 16},
            10, // Color: Light green
            0 // Parallel
            });
    }

    subPortals.push_back({
        {PLAY_AREA_RIGHT - 16 * 11, PLAY_AREA_BOTTOM - 16 * 2, 16, 16},
        {PLAY_AREA_RIGHT - 16 * 8, PLAY_AREA_BOTTOM - 16 * 2, 16, 16},
        9, // Color: Orange
        1
        });
    //...
}