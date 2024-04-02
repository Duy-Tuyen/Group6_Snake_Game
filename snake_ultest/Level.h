#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>

#include "Snake.h"

// Define the playable area boundaries
extern const int PLAY_AREA_LEFT;
extern const int PLAY_AREA_RIGHT;
extern const int PLAY_AREA_TOP;
extern const int PLAY_AREA_BOTTOM;

extern int currentLevel; // Current level of the game

extern bool goInGate_progress;
extern bool goOutGate_progress;

// Structure to represent an obstacle
struct Obstacle {
    int x, y, w, h;
};

struct subPortal {
    struct Obstacle in;
    struct Obstacle out;
    int color_code;
    bool parallel;
};

extern std::vector<bool> gate_open_step;

extern std::vector<Obstacle> obstacles; // Vector to store obstacles
extern std::vector<Obstacle> portals; // Vector to store portals
extern std::vector<Obstacle> moving_obstacles; // Vector to store moving obstacles

extern std::vector<Obstacle> monsters; // Vector to store monsters

extern std::vector<subPortal> subPortals; // Vector to store subPortals


// Function to render obstacles on the screen
void RenderObstacles(SDL_Renderer* renderer);
void RenderPortals(SDL_Renderer* renderer);
void RenderMovingObstacles(SDL_Renderer* renderer);

// Function to check collision between the snake and obstacles
bool CheckCollisionWithObstacles(int posX, int posY, int width, int height);

bool CheckCollisionWithPortals(int posX, int posY, int width, int height);

void AddObstacle(int x, int y, int w, int h);

void AddPortal(int x, int y, int w, int h);

void RemoveObstacle(int x, int y);

void wall();

void Obstacle_level_1();

void Obstacle_level_2();

void Obstacle_level_3();

void gate_in();

void gate_out();

void goInGate_check();

void goOutGate_check();

void Level(int levelNumber);

void nextLevel();

void RenderHitbox(SDL_Renderer* renderer, int x, int y, int w, int h);

void movingObstalceLevel4();

void renderMonster();

void toggleObstacleLevel3();

void RenderToggleObstacles_Draw_Level3();

void RenderToggleObstacles_Fill_Level3();

bool toggleObstacleCollision();

void RenderSubPortal(SDL_Renderer* renderer);

void subPortalLevel5();

void snakeTeleport_in_to_out();
void snakeTeleport_out_to_in();

void gate_out1();

void gate_out2();

void gate_out3();

void gate_out4();

void gate_open();