#include "Level.h"

// Define the playable area boundaries
const int PLAY_AREA_LEFT = 50;
const int PLAY_AREA_RIGHT = 658;
const int PLAY_AREA_TOP = 50;
const int PLAY_AREA_BOTTOM = 466;

int currentLevel = 1; // Current level of the game

bool goInGate_progress = false;
bool goOutGate_progress = false;

bool toggleObstacleLevel2_start = false;
bool movingObstacleLevel3_start = false;

std::vector<Obstacle> obstacles; // Vector to store obstacles
std::vector<Obstacle> portals; // Vector to store portals
std::vector<Obstacle> moving_obstacles; // Vector to store moving obstacles

std::vector<Obstacle> monsters; // Vector to store monsters

std::vector<Obstacle> toggle_obstacles; // Vector to store toggle obstacles

std::vector<subPortal> subPortals; // Vector to store subPortals

std::vector<Obstacle> ice_tiles; // Vector to store ice blocks

std::vector<subPortal> icePortals; // Vector to store ice portals


void setRenderColor(int colorCode) {
    switch (colorCode) {
    case 1:
        SDL_SetRenderDrawColor(g_renderer, 204, 229, 255, 0); // Set obstacle color (while)
		break;
    default:
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 0); // Set obstacle color (red)
		break;
    }
}

// Function to render obstacles on the screen
void RenderObstacles(SDL_Renderer* renderer) {
    for (const auto& obstacle : obstacles) {
        setRenderColor(obstacle.c);
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

// Portal as block. render pos is automatically set when real pos change
/*
void RenderSubPortal_Level4(SDL_Renderer* renderer) {
    for (const auto& subportal : subPortals) {
        if (loopCounter % 10 >= 0 && loopCounter % 10 <= 4) {
            switch (subportal.color_code) {
            case 1:
                g_subPortal = LoadTexture("Portal_Blue_1_Down.png");
                ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
                g_subPortal = LoadTexture("Portal_Blue_2_Down.png");
                ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
                break;
            case 2:
                g_subPortal = LoadTexture("Portal_Green_1_Left.png");
				ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
				g_subPortal = LoadTexture("Portal_Green_2_Right.png");
				ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
				break;
            case 3:
                g_subPortal = LoadTexture("Portal_Purple_1.png");
                ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
                g_subPortal = LoadTexture("Portal_Purple_2.png");
                ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
                break;
            case 4:
                g_subPortal = LoadTexture("Portal_Yellow_1_Left.png");
				ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
				g_subPortal = LoadTexture("Portal_Yellow_2_Right.png");
				ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
				break;
            }
        }
        else {
            switch (subportal.color_code) {
            case 1:
                g_subPortal = LoadTexture("Portal_Blue_2_Down.png");
				ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
				g_subPortal = LoadTexture("Portal_Blue_1_Down.png");
				ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
				break;
            case 2:
                g_subPortal = LoadTexture("Portal_Green_2_Left.png");
                ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
                g_subPortal = LoadTexture("Portal_Green_1_Right.png");
                ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
                break;
            case 3:
                g_subPortal = LoadTexture("Portal_Purple_2.png");
				ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
				g_subPortal = LoadTexture("Portal_Purple_1.png");
				ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
				break;
            case 4:
                g_subPortal = LoadTexture("Portal_Yellow_2_Left.png");
				ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
				g_subPortal = LoadTexture("Portal_Yellow_1_Right.png");
				ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
				break;
            }
        }

        if (subportal.color_code == 5) {
            g_subPortal = LoadTexture("Blue centre.png");
            ApplyTexture2(g_subPortal, subportal.in.x - subportal.in.w / 2, subportal.in.y - subportal.in.h / 2, subportal.in.w, subportal.in.h);
            ApplyTexture2(g_subPortal, subportal.out.x - subportal.out.w / 2, subportal.out.y - subportal.out.h / 2, subportal.out.w, subportal.out.h);
        }
    }
}
*/

// Portal not as block, have to manually set render pos when real pos change
void RenderSubPortal_Level4(SDL_Renderer* renderer) {
    if (currentLevel == 4) {
        int x, y;
        if (loopCounter % 10 >= 0 && loopCounter % 10 <= 4) {

            g_subPortal = LoadTexture("Portal_Blue_1_Down.png");
            x = PLAY_AREA_LEFT + 16 * 5 + 8;
            y = PLAY_AREA_TOP + 16 * 1;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Blue_2_Down.png");
            x = PLAY_AREA_LEFT + 16 * 15 + 8;
            y = PLAY_AREA_TOP + 16 * 1;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Green_1_Left.png");
            x = PLAY_AREA_LEFT + 16 * 20;
            y = PLAY_AREA_TOP + 16 * 4;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 * 3 / 2, 16, 16 * 3);

            g_subPortal = LoadTexture("Portal_Green_2_Right.png");
            x = PLAY_AREA_LEFT + 16 * 21;
            y = PLAY_AREA_TOP + 16 * 9;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 * 3 / 2, 16, 16 * 3);

            g_subPortal = LoadTexture("Portal_Purple_1.png");
            x = PLAY_AREA_LEFT + 16 * 24 + 8;
            y = PLAY_AREA_TOP + 16 * 13;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Purple_2.png");
            x = PLAY_AREA_LEFT + 16 * 5 + 8;
            y = PLAY_AREA_TOP + 16 * 18;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Yellow_1_Left.png");
            x = PLAY_AREA_RIGHT - 16 * 11;
            y = PLAY_AREA_BOTTOM - 16 * 2;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);

            g_subPortal = LoadTexture("Portal_Yellow_2_Right.png");
            x = PLAY_AREA_RIGHT - 16 * 8;
            y = PLAY_AREA_BOTTOM - 16 * 2;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);

            g_subPortal = LoadTexture("Blue centre.png");
            x = PLAY_AREA_RIGHT - 16 * 7;
            y = PLAY_AREA_TOP + 16 * 7;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);
            x = PLAY_AREA_LEFT + 16 * 20;
            y = PLAY_AREA_BOTTOM - 16 * 7;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);

        }
        else {

            g_subPortal = LoadTexture("Portal_Blue_2_Down.png");
            x = PLAY_AREA_LEFT + 16 * 5 + 8;
            y = PLAY_AREA_TOP + 16 * 1;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Blue_1_Down.png");
            x = PLAY_AREA_LEFT + 16 * 15 + 8;
            y = PLAY_AREA_TOP + 16 * 1;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Green_2_Left.png");
            x = PLAY_AREA_LEFT + 16 * 20;
            y = PLAY_AREA_TOP + 16 * 4;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 * 3 / 2, 16, 16 * 3);

            g_subPortal = LoadTexture("Portal_Green_1_Right.png");
            x = PLAY_AREA_LEFT + 16 * 21;
            y = PLAY_AREA_TOP + 16 * 9;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 * 3 / 2, 16, 16 * 3);

            g_subPortal = LoadTexture("Portal_Purple_2.png");
            x = PLAY_AREA_LEFT + 16 * 24 + 8;
            y = PLAY_AREA_TOP + 16 * 13;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Purple_1.png");
            x = PLAY_AREA_LEFT + 16 * 5 + 8;
            y = PLAY_AREA_TOP + 16 * 18;
            ApplyTexture2(g_subPortal, x - 16 * 4 / 2, y - 16 / 2, 16 * 4, 16);

            g_subPortal = LoadTexture("Portal_Yellow_2_Left.png");
            x = PLAY_AREA_RIGHT - 16 * 11;
            y = PLAY_AREA_BOTTOM - 16 * 2;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);

            g_subPortal = LoadTexture("Portal_Yellow_1_Right.png");
            x = PLAY_AREA_RIGHT - 16 * 8;
            y = PLAY_AREA_BOTTOM - 16 * 2;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);

            g_subPortal = LoadTexture("Blue centre.png");
            x = PLAY_AREA_RIGHT - 16 * 7;
            y = PLAY_AREA_TOP + 16 * 7;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);
            x = PLAY_AREA_LEFT + 16 * 20;
            y = PLAY_AREA_BOTTOM - 16 * 7;
            ApplyTexture2(g_subPortal, x - 16 / 2, y - 16 / 2, 16, 16);

        }
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

void obstacle_level_1() {
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

void Obstacle_level_3() {
    int x, y;
    int n = 9, m = 11;
    int obstacle_size = 16;

    y = PLAY_AREA_TOP + 16 * 6;
    for (x = PLAY_AREA_LEFT + 16 * 12; x <= PLAY_AREA_LEFT + 16 * 13; x += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}
    n = 12, m = 14;
    for (int i = 7; i <= 13; i++) {
        for (int j = n; j <= m; j++) {
            AddObstacle(PLAY_AREA_LEFT + 16 * j, PLAY_AREA_TOP + 16 * i, obstacle_size, obstacle_size);
        }
        n++;
        m++;
    }

    y = PLAY_AREA_TOP + 16 * 6;
    for (x = PLAY_AREA_RIGHT - 16 * 12; x >= PLAY_AREA_RIGHT - 16 * 13; x -= obstacle_size) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }
    n = 12, m = 14;
    for (int i = 7; i <= 13; i++) {
        for (int j = n; j <= m; j++) {
            AddObstacle(PLAY_AREA_RIGHT - 16 * j, PLAY_AREA_TOP + 16 * i, obstacle_size, obstacle_size);
        }
        n++;
        m++;
    }

    y = PLAY_AREA_BOTTOM - 16 * 6;
    for (x = PLAY_AREA_LEFT + 16 * 12; x <= PLAY_AREA_LEFT + 16 * 13; x += obstacle_size) {
		AddObstacle(x, y, obstacle_size, obstacle_size);
	}
    n = 12, m = 14;
    for (int i = 7; i <= 13; i++) {
        for (int j = n; j <= m; j++) {
			AddObstacle(PLAY_AREA_LEFT + 16 * j, PLAY_AREA_BOTTOM - 16 * i, obstacle_size, obstacle_size);
		}
		n++;
		m++;
	}

    y = PLAY_AREA_BOTTOM - 16 * 6;
    for (x = PLAY_AREA_RIGHT - 16 * 12; x >= PLAY_AREA_RIGHT - 16 * 13; x -= obstacle_size) {
        AddObstacle(x, y, obstacle_size, obstacle_size);
    }
    n = 12, m = 14;
    for (int i = 7; i <= 13; i++) {
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
    */
    
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

void gate_open_level() {
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

void gate_open_special() {
    if (gate_open_step[0]) {
        gate_out1();
        gate_open_step[0] = false;
        gate_open_step[1] = true;
        return;
    }
    if (gate_open_step[1]) {
        obstacles.clear();
        subPortals.clear();
        Level_Special(currentLevel);
        gate_out2();
        gate_open_step[1] = false;
        gate_open_step[2] = true;
        return;
    }
    if (gate_open_step[2]) {
        obstacles.clear();
        subPortals.clear();
        Level_Special(currentLevel);
        gate_out3();
        gate_open_step[2] = false;
        gate_open_step[3] = true;
        lockMovement = false;
        return;
    }
    if (gate_open_step[3]) {
        obstacles.clear();
        subPortals.clear();
        Level_Special(currentLevel);
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

    if (specialMode) {
        for (x = left; x <= right; x++) {
			obstacles.push_back({ x, top, 16, 16, 1 });
            obstacles.push_back({ x, bottom, 16, 16, 1 });
		}

		for (y = top; y <= bottom; y++) {
            obstacles.push_back({ left, y, 16, 16, 1 });
			obstacles.push_back({ right, y, 16, 16, 1 });
		}
    }
    else {

        for (x = left; x <= right; x++) {
            AddObstacle(x, top, 16, 16);
            AddObstacle(x, bottom, 16, 16);
        }

        for (y = top; y <= bottom; y++) {
            AddObstacle(left, y, 16, 16);
            AddObstacle(right, y, 16, 16);
        }
    }
}

void Level(int levelNumber) {
    // Adjust game parameters based on the level number
    switch (levelNumber) {
    case 1:
        // Level 1 settings
        // Set obstacle position and dimensions for level 1
        wall();
        obstacle_level_1();

        break;
    case 2:
        // Level 2 settings
        // Set obstacle position and dimensions for level 2
        wall();
        toggleObstacleLevel2();
        toggleObstacleLevel2_start = true;


        break;
        // Add more cases for additional levels
    case 3:
        // Level 3 settings
        // Set obstacle position and dimensions for level 3
        wall();
        Obstacle_level_3();
        subPortalLevel3();
        movingObstacleLevel3_start = true;


        break;
    case 4:
        // Level 4 settings
        // Set obstacle position and dimensions for level 4
        wall();
        subPortalLevel4();


        break;
    case 5:
        wall();

        break;

    default:
        // Default level settings
        // Set default obstacle position and dimensions
        wall();

        break;
    }
}

void Level_Special(int levelNumber) {
    switch (levelNumber) {
	case 1:
        wall();
        iceTile_LevelSP1();
		break;

	default:
        wall();
		break;
	}

}

void levelClear() {

    obstacles.clear();
	subPortals.clear();
	monsters.clear();
	portals.clear();
    ice_tiles.clear();
    toggle_obstacles.clear();
    moving_obstacles_direction.clear();

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
        if (currentLevel == 3) isMovingMonster = true;

        if (specialMode) Level_Special(currentLevel);
		else Level(currentLevel);

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


void toggleObstacleLevel2() {
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

void RenderToggleObstacles_Draw_Level2() {
    if (toggleObstacleLevel2_start) {
        loopCounter = 0;
        toggleObstacleLevel2_start = false;
    }
    if (currentLevel == 2) {
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

void RenderToggleObstacles_Fill_Level2() {
    if (toggleObstacleLevel2_start) {
        loopCounter = 0;
        toggleObstacleLevel2_start = false;
    }
    if (currentLevel == 2) {
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

void RenderIceTile(SDL_Renderer* renderer) {
    for (const auto& icetile : ice_tiles) {
        ApplyTexture2(g_iceTile, icetile.x - 16 / 2, icetile.y - 16 / 2, 16, 16);
    }
}

bool toggleObstacleCollision() {
    if (currentLevel == 2) {
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

void movingObstalceLevel3() {
    if (isMovingMonster) {
        if (movingObstacleLevel3_start) {
            monsters.push_back({ PLAY_AREA_RIGHT - 16 * 5, PLAY_AREA_TOP + 16 * 4, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::LEFT);
            monsters.push_back({ PLAY_AREA_LEFT + 16 * 5, PLAY_AREA_BOTTOM - 16 * 4, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::RIGHT);
            
            monsters.push_back({ PLAY_AREA_LEFT + 16 * 19, PLAY_AREA_TOP + 16 * 4, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::LEFT);
            monsters.push_back({ PLAY_AREA_RIGHT - 16 * 19, PLAY_AREA_BOTTOM - 16 * 4, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::RIGHT);
            
            monsters.push_back({ PLAY_AREA_LEFT + 16 * 5, PLAY_AREA_TOP + 16 * 4, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::DOWN);
            monsters.push_back({ PLAY_AREA_RIGHT - 16 * 5, PLAY_AREA_BOTTOM - 16 * 4, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::UP);
            
            monsters.push_back({ PLAY_AREA_LEFT + 16 * 5, PLAY_AREA_TOP + 16 * 13, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::DOWN);
            monsters.push_back({ PLAY_AREA_RIGHT - 16 * 5, PLAY_AREA_BOTTOM - 16 * 13, 16 * 3, 16 * 3 });
            moving_obstacles_direction.push_back(Direction::UP);
            
        }
        movingObstacleLevel3_start = false;
    }
    
    int moving_obstacle_speed = 16;
    if (loopCounter % 2 == 0 && !pause) {
        for (int i = 0; i < monsters.size(); i++) {
            if (currentLevel == 3) {
                switch (moving_obstacles_direction[i]) {
                case RIGHT:
                    if (monsters[i].x != PLAY_AREA_RIGHT - 16 * 5) {
                        monsters[i].x += moving_obstacle_speed;
                    }
                    else {
                        moving_obstacles_direction[i] = UP;
                        monsters[i].y -= moving_obstacle_speed;
                    }
                    break;
                case LEFT:
                    if (monsters[i].x != PLAY_AREA_LEFT + 16 * 5) {
                        monsters[i].x -= moving_obstacle_speed;
                    }
                    else {
                        moving_obstacles_direction[i] = DOWN;
                        monsters[i].y += moving_obstacle_speed;
                    }
                    break;
                case UP:
                    if (monsters[i].y != PLAY_AREA_TOP + 16 * 4) {
                        monsters[i].y -= moving_obstacle_speed;
                    }
                    else {
                        moving_obstacles_direction[i] = LEFT;
                        monsters[i].x -= moving_obstacle_speed;
                    }
                    break;
                case DOWN:
                    if (monsters[i].y != PLAY_AREA_BOTTOM - 16 * 4) {
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
    if (currentLevel == 4) {
        monsters.clear();
        moving_obstacles_direction.clear();
    }
}

void snakeTeleport_in_to_out(std::vector<subPortal> typePortals) {
    for (const auto& typeportal : typePortals) {
        int distanceX = abs(snakeX - typeportal.in.x);
        int distanceY = abs(snakeY - typeportal.in.y);
        int edgeDistanceX = (snakeWidth + typeportal.in.w) / 2;
        int edgeDistanceY = (snakeHeight + typeportal.in.h) / 2;
        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
            if (typeportal.tele == 1) { // parallel
                switch (snakeDirection) {
                case UP:
                    snakeX = typeportal.out.x;
                    snakeY = typeportal.out.y - 16;
                    break;
                case DOWN:
                    snakeX = typeportal.out.x;
                    snakeY = typeportal.out.y + 16;
                    break;
                case LEFT:
                    snakeX = typeportal.out.x - 16;
                    snakeY = typeportal.out.y;
                    break;
                case RIGHT:
                    snakeX = typeportal.out.x + 16;
                    snakeY = typeportal.out.y;
                    break;
                }
            }
            else if (typeportal.tele == 0) { // anti parallel

                switch (snakeDirection) {
                case UP:
                    lastDirection = DOWN;
                    snakeDirection = DOWN;
                    snakeX = typeportal.out.x;
                    snakeY = typeportal.out.y + 16;
                    break;
                case DOWN:
                    lastDirection = UP;
                    snakeDirection = UP;
                    snakeX = typeportal.out.x;
                    snakeY = typeportal.out.y - 16;
                    break;
                case LEFT:
                    lastDirection = RIGHT;
                    snakeDirection = RIGHT;
                    snakeX = typeportal.out.x + 16;
                    snakeY = typeportal.out.y;
                    break;
                case RIGHT:
                    lastDirection = LEFT;
                    snakeDirection = LEFT;
                    snakeX = typeportal.out.x - 16;
                    snakeY = typeportal.out.y;
                    break;
                }

            }
            else if (typeportal.tele == 2) { // right to up / down to left
                switch (snakeDirection) {
                case UP:
                    lastDirection = RIGHT;
                    snakeDirection = RIGHT;
                    snakeX = typeportal.out.x + 16;
                    snakeY = typeportal.out.y;
                    break;
                case DOWN:
                    lastDirection = LEFT;
                    snakeDirection = LEFT;
                    snakeX = typeportal.out.x - 16;
                    snakeY = typeportal.out.y;
                    break;
                case LEFT:
                    lastDirection = DOWN;
                    snakeDirection = DOWN;
                    snakeX = typeportal.out.x;
                    snakeY = typeportal.out.y + 16;
                    break;
                case RIGHT:
                    lastDirection = UP;
                    snakeDirection = UP;
                    snakeX = typeportal.out.x;
                    snakeY = typeportal.out.y - 16;
                    break;
                }
            }
        }
    }
}

void snakeTeleport_out_to_in(std::vector<subPortal> typePortals) {
    for (const auto& typeportal : typePortals) {
        int distanceX = abs(snakeX - typeportal.out.x);
        int distanceY = abs(snakeY - typeportal.out.y);
        int edgeDistanceX = (snakeWidth + typeportal.out.w) / 2;
        int edgeDistanceY = (snakeHeight + typeportal.out.h) / 2;
        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
            if (typeportal.tele == 1) {
                switch (snakeDirection) {
                case UP:
                    snakeX = typeportal.in.x;
                    snakeY = typeportal.in.y - 16;
                    break;
                case DOWN:
                    snakeX = typeportal.in.x;
                    snakeY = typeportal.in.y + 16;
                    break;
                case LEFT:
                    snakeX = typeportal.in.x - 16;
                    snakeY = typeportal.in.y;
                    break;
                case RIGHT:
                    snakeX = typeportal.in.x + 16;
                    snakeY = typeportal.in.y;
                    break;
                }
            }
            else if (typeportal.tele == 0) {
                switch (snakeDirection) {
                case UP:
                    lastDirection = DOWN;
                    snakeDirection = DOWN;
                    snakeX = typeportal.in.x;
                    snakeY = typeportal.in.y + 16;
                    break;
                case DOWN:
                    lastDirection = UP;
                    snakeDirection = UP;
                    snakeX = typeportal.in.x;
                    snakeY = typeportal.in.y - 16;
                    break;
                case LEFT:
                    lastDirection = RIGHT;
                    snakeDirection = RIGHT;
                    snakeX = typeportal.in.x + 16;
                    snakeY = typeportal.in.y;
                    break;
                case RIGHT:
                    lastDirection = LEFT;
                    snakeDirection = LEFT;
                    snakeX = typeportal.in.x - 16;
                    snakeY = typeportal.in.y;
                    break;
                }
            }
            else if (typeportal.tele == 2) {
                switch (snakeDirection) {
                case UP:
                    lastDirection = RIGHT;
                    snakeDirection = RIGHT;
                    snakeX = typeportal.in.x + 16;
                    snakeY = typeportal.in.y;
                    break;
                case DOWN:
                    lastDirection = LEFT;
                    snakeDirection = LEFT;
                    snakeX = typeportal.in.x - 16;
                    snakeY = typeportal.in.y;
                    break;
                case LEFT:
                    lastDirection = DOWN;
                    snakeDirection = DOWN;
                    snakeX = typeportal.in.x;
                    snakeY = typeportal.in.y + 16;
                    break;
                case RIGHT:
                    lastDirection = UP;
                    snakeDirection = UP;
                    snakeX = typeportal.in.x;
                    snakeY = typeportal.in.y - 16;
                    break;
                }
            }
        }
    }
}


void subPortalLevel3() {
    subPortals.push_back({
        {PLAY_AREA_LEFT + 16 * 17, PLAY_AREA_TOP + 16 * 13, 16, 16},
        {PLAY_AREA_LEFT + 16 * 21, PLAY_AREA_TOP + 16 * 13, 16, 16},
        2,
        1
        });
}

void subPortalLevel4() {
    // Obstacle setup
    
    // Top Left field
    for (int i = 0; i <= 9; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * (1 + i), PLAY_AREA_TOP + 16 * 1, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (1 + i), PLAY_AREA_TOP + 16 * 17, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (1 + i), PLAY_AREA_TOP + 16 * 18, 16, 16);
    }

    // Top middle field
    for (int i = 0; i <= 9; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * (11 + i), PLAY_AREA_TOP + 16 * 1, 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * (11 + i), PLAY_AREA_TOP + 16 * 12, 16, 16);
    }

    for (int i = 0; i <= 9; i++) {
        AddObstacle(PLAY_AREA_LEFT + 16 * 11, PLAY_AREA_TOP + 16 * (2 + i), 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (2 + i), 16, 16);
        AddObstacle(PLAY_AREA_LEFT + 16 * 21, PLAY_AREA_TOP + 16 * (2 + i), 16, 16);
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
            1, // 
            0 // No tele
            });
    }

    for (int i = 0; i <= 2; i++) {
        RemoveObstacle(PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (3 + i));
        RemoveObstacle(PLAY_AREA_LEFT + 16 * 21, PLAY_AREA_TOP + 16 * (8+ i));

        subPortals.push_back({
            {PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * (3 + i), 16, 16},
            {PLAY_AREA_LEFT + 16 * 21, PLAY_AREA_TOP + 16 * (8 + i), 16, 16},
            2, // 
            1 // tele
            });
    }

    for (int i = 0; i <= 3; i++) {
        RemoveObstacle(PLAY_AREA_LEFT + 16 * (23 + i), PLAY_AREA_TOP + 16 * 13);
        RemoveObstacle(PLAY_AREA_LEFT + 16 * (4 + i), PLAY_AREA_BOTTOM - 16 * 8);

        subPortals.push_back({
            {PLAY_AREA_LEFT + 16 * (23 + i), PLAY_AREA_TOP + 16 * 13, 16, 16},
            {PLAY_AREA_LEFT + 16 * (4 + i), PLAY_AREA_BOTTOM - 16 * 8, 16, 16},
            3, //
            0 // non tele
            });
    }

    subPortals.push_back({
        {PLAY_AREA_RIGHT - 16 * 11, PLAY_AREA_BOTTOM - 16 * 2, 16, 16},
        {PLAY_AREA_RIGHT - 16 * 8, PLAY_AREA_BOTTOM - 16 * 2, 16, 16},
        4, // 
        1
        });
    //...

    subPortals.push_back({
        {PLAY_AREA_RIGHT - 16 * 7, PLAY_AREA_TOP + 16 * 7, 16, 16},
        {PLAY_AREA_LEFT + 16 * 20, PLAY_AREA_TOP + 16 * 19, 16, 16},
        5, // 
        1 // tele
        });
}

void mapTile(int tile_color) {
    switch (tile_color) {
    case 1:
        SDL_SetRenderDrawColor(g_renderer, 255, 153, 153, 0); // Set tile_1 color (somewhat light red)
        for (int j = 1; j <= 25; j++) {
            for (int i = (j % 2) == 0 ? 1 : 2; i <= 37; i += 2) {
                SDL_Rect tileRect = { PLAY_AREA_LEFT + 16 * i - 16 / 2, PLAY_AREA_TOP + 16 * j - 16 / 2, 16, 16 };
                SDL_RenderFillRect(g_renderer, &tileRect); // Render tile_1
            }
        }

        SDL_SetRenderDrawColor(g_renderer, 255, 204, 204, 0); // Set tile_2 color (light red)
        for (int j = 1; j <= 25; j++) {
            for (int i = (j % 2) != 0 ? 1 : 2; i <= 37; i += 2) {
                SDL_Rect tileRect = { PLAY_AREA_LEFT + 16 * i - 16 / 2, PLAY_AREA_TOP + 16 * j - 16 / 2, 16, 16 };
                SDL_RenderFillRect(g_renderer, &tileRect); // Render tile_2
            }
        }
        break;
    case 2:
        SDL_SetRenderDrawColor(g_renderer, 0, 204, 204, 0); // Set tile_1 color (white)
        for (int j = 1; j <= 25; j++) {
            for (int i = (j % 2) == 0 ? 1 : 2; i <= 37; i += 2) {
                SDL_Rect tileRect = { PLAY_AREA_LEFT + 16 * i - 16 / 2, PLAY_AREA_TOP + 16 * j - 16 / 2, 16, 16 };
                SDL_RenderFillRect(g_renderer, &tileRect); // Render tile_1
            }
        }

        SDL_SetRenderDrawColor(g_renderer, 153, 255, 255, 0); // Set tile_2 color (light blue)
        for (int j = 1; j <= 25; j++) {
            for (int i = (j % 2) != 0 ? 1 : 2; i <= 37; i += 2) {
                SDL_Rect tileRect = { PLAY_AREA_LEFT + 16 * i - 16 / 2, PLAY_AREA_TOP + 16 * j - 16 / 2, 16, 16 };
                SDL_RenderFillRect(g_renderer, &tileRect); // Render tile_2
            }
        }
    }
}

void iceTileLogic() {
    for (const auto& icetile : ice_tiles) {
        if (snakeX == icetile.x && snakeY == icetile.y) {
            lockDir = true;
            return;
        }
        else {
            lockDir = false;
        }
    }
}

void RemoveIceTile(int x, int y) {
    for (auto it = ice_tiles.begin(); it != ice_tiles.end(); ++it) {
        if (it->x == x && it->y == y) {
            ice_tiles.erase(it);
            break;
        }
    }
}

void iceTile_LevelSP1() {

    int x, y;

    // Ice Tile
    for (y = PLAY_AREA_TOP + 16 * 5; y <= PLAY_AREA_BOTTOM - 16 * 5; y += 16) {

        for (x = PLAY_AREA_LEFT + 16 * 11; x <= PLAY_AREA_RIGHT - 16 * 11; x += 16) {

            ice_tiles.push_back({ x, y, 16, 16 });

        }
    }

    // Obstacle
    x = PLAY_AREA_LEFT + 16 * 11;
    y = PLAY_AREA_TOP + 16 * 5;
    
    obstacles.push_back({ x, y , 16 * 3, 16, 1 });

    x = PLAY_AREA_RIGHT - 16 * 11;
    y = PLAY_AREA_TOP + 16 * 6;
    obstacles.push_back({ x, y, 16 * 3, 16, 1 });

    x = PLAY_AREA_LEFT + 16 * 10;
    y = PLAY_AREA_TOP + 16 * 13;
    obstacles.push_back({ x, y, 16 * 3, 16, 1 });

    x = PLAY_AREA_RIGHT - 16 * 10;
    y = PLAY_AREA_BOTTOM - 16 * 8;
    obstacles.push_back({ x, y, 16 * 3, 16, 1 });

    int n = 7;
    for (int j = 0; j <= 7; j++) {
        for (int i = 0; i <= n; i++) {
            x = PLAY_AREA_LEFT + 16 * (16 + i);
			y = PLAY_AREA_TOP + 16 * (11 + j);
			obstacles.push_back({ x, y, 16, 16, 1 });
        }

        n--;
    }
    
    x = PLAY_AREA_RIGHT - 16 * 2 - 8;
    y = PLAY_AREA_TOP + 16 * 11;
    obstacles.push_back({ x, y, 16 * 4, 16, 1 });

    x = PLAY_AREA_RIGHT - 16 * 2 - 8;
	y = PLAY_AREA_BOTTOM - 16 * 11;
    obstacles.push_back({ x, y, 16 * 4, 16, 1 });

    x = PLAY_AREA_RIGHT - 16 * 4;
    y = PLAY_AREA_BOTTOM - 16 * 13;
    obstacles.push_back({ x, y, 16, 16 * 3, 1 });

    // subPortal
    for (int i = 0, j = 0; j <= 2; i++, j++) {
        RemoveObstacle(PLAY_AREA_LEFT + 16 * 16, PLAY_AREA_BOTTOM - 16 * (12 + j));
        RemoveObstacle(PLAY_AREA_RIGHT - 16 * (18 + i), PLAY_AREA_TOP + 16 * 11);

        icePortals.push_back({
            {PLAY_AREA_LEFT + 16 * 16, PLAY_AREA_BOTTOM - 16 * (12 + j), 16, 16},
            {PLAY_AREA_RIGHT - 16 * (18 + i), PLAY_AREA_TOP + 16 * 11, 16, 16},
            1,
            2
            });
    }

    RemoveObstacle(PLAY_AREA_RIGHT - 16 * 18, PLAY_AREA_BOTTOM - 16 * 12);
    RemoveObstacle(PLAY_AREA_RIGHT - 16 * 16, PLAY_AREA_TOP + 16 * 7);
    icePortals.push_back({
		{PLAY_AREA_RIGHT - 16 * 18, PLAY_AREA_BOTTOM - 16 * 12, 16, 16},
		{PLAY_AREA_RIGHT - 16 * 16, PLAY_AREA_TOP + 16 * 7, 16, 16},
		2,
		1
		});

    RemoveObstacle(PLAY_AREA_RIGHT - 16 * 13, PLAY_AREA_BOTTOM - 16 * 6);
    RemoveObstacle(PLAY_AREA_RIGHT - 16 * 3, PLAY_AREA_BOTTOM - 16 * 13);
    icePortals.push_back({
        {PLAY_AREA_RIGHT - 16 * 18, PLAY_AREA_TOP + 16 * 5, 16, 16},
        {PLAY_AREA_RIGHT - 16 * 13, PLAY_AREA_BOTTOM - 16 * 6, 16, 16},
        3,
        1
        });

    RemoveObstacle(PLAY_AREA_RIGHT - 16 * 13, PLAY_AREA_BOTTOM - 16 * 8);
    RemoveObstacle(PLAY_AREA_RIGHT - 16 * 3, PLAY_AREA_TOP + 16 * 13);
    icePortals.push_back({
		{PLAY_AREA_RIGHT - 16 * 13, PLAY_AREA_BOTTOM - 16 * 8, 16, 16},
		{PLAY_AREA_RIGHT - 16 * 3, PLAY_AREA_TOP + 16 * 13, 16, 16},
		4,
		2
		});

}

void RenderIcePortal() {
    for (const auto& iceportal : icePortals) {
        if (loopCounter % 10 >= 0 && loopCounter % 10 <= 4) {
            switch (iceportal.color_code) {
            case 1:
                g_icePortal = LoadTexture("icePortal_Blue_1.png");
                ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
                ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
                break;
            case 2:
                g_icePortal = LoadTexture("icePortal_Green_1.png");
				ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
				ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
				break;
            case 3:
                g_icePortal = LoadTexture("icePortal_Yellow_1.png");
                ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
                ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
                break;
            case 4:
                g_icePortal = LoadTexture("icePortal_Pink_1.png");
                ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
                ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
                break;
            }
        }
        else {
            switch (iceportal.color_code) {
			case 1:
				g_icePortal = LoadTexture("icePortal_Blue_2.png");
				ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
				ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
				break;
            case 2:
                g_icePortal = LoadTexture("icePortal_Green_2.png");
				ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
				ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
				break;
            case 3:
                g_icePortal = LoadTexture("icePortal_Yellow_2.png");
                ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
                ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
                break;
            case 4:
                g_icePortal = LoadTexture("icePortal_Pink_2.png");
                ApplyTexture2(g_icePortal, iceportal.in.x - 16 / 2, iceportal.in.y - 16 / 2, 16, 16);
                ApplyTexture2(g_icePortal, iceportal.out.x - 16 / 2, iceportal.out.y - 16 / 2, 16, 16);
                break;
			}
        }
    }
}