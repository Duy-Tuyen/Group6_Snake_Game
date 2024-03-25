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

// Structure to represent an obstacle
struct Obstacle {
    int x, y, w, h;
};

extern std::vector<Obstacle> obstacles; // Vector to store obstacles
extern std::vector<Obstacle> portals; // Vector to store portals

// Function to render obstacles on the screen
void RenderObstacles(SDL_Renderer* renderer);
void RenderPortals(SDL_Renderer* renderer);

// Function to check collision between the snake and obstacles
bool CheckCollisionWithObstacles(int posX, int posY, int width, int height);

bool CheckCollisionWithPortals(int posX, int posY, int width, int height);

void AddObstacle(int x, int y, int w, int h);

void AddPortal(int x, int y, int w, int h);

void RemoveObstacle(int x, int y);

void Obstacle_level_1();

void Obstacle_level_2();

void Obstacle_level_3();

void gate();

void Level(int levelNumber);

void nextLevel();

void RenderHitbox(SDL_Renderer* renderer, int x, int y, int w, int h);