#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>

#include "Snake.h"

// Structure to represent an obstacle
struct Obstacle {
    int x, y, w, h, c;
};

struct subPortal {
    struct Obstacle in;
    struct Obstacle out;
    int color_code;
    int tele;
};

// Define the playable area boundaries
extern const int PLAY_AREA_LEFT;
extern const int PLAY_AREA_RIGHT;
extern const int PLAY_AREA_TOP;
extern const int PLAY_AREA_BOTTOM;
// ------------------------------------------------

extern int currentLevel; // Current level of the game

// Flag:
extern bool goInGate_progress; // Flag to activate the progress of going into the gate
extern bool goOutGate_progress; // Flag to activate the progress of going out of the gate
extern bool gate_open_done; // Flag to check if the going out gate is done

extern bool toggleObstacleLevel2_start;
extern bool movingObstacleLevel3_start;

// Manage monster movement when pause
extern bool fixed1WhenPause;
extern bool fixed2WhenPause;

extern bool isMovingMonster;

extern bool dreamFlag; // Flag to check the instant moment when the snake is out of dream after being in dream (to manage lockDir)
// ------------------------------------------------

// Vector:
extern std::vector<bool> gate_open_step;

extern std::vector<Obstacle> obstacles; // Vector to store obstacles

extern std::vector<Obstacle> portals; // Actually gate portal

extern std::vector<Obstacle> toggle_obstacles; // Vector to store toggle obstacles

extern std::vector<Obstacle> monsters; // Vector to store monsters

extern std::vector<subPortal> subPortals; // Actually the portal that teleport in and out when playing (not the gate)
extern std::vector<subPortal> icePortals; // Actually subPortal but in special mode

extern std::vector<Obstacle> fixedFood; // Vector to store fixed food (only in special mode)

extern std::vector<Obstacle> ice_tiles; // Vector to store ice blocks

extern std::vector<Obstacle> dreamBlocks; // Vector to store dream blocks
// ------------------------------------------------

// Collision:
bool isInObstacle(int x, int y, int width, int heigth);
bool isInToggleObstacle(Obstacle toggle_obstacle, int x, int y, int width, int height);
bool isInDream(int x, int y);
bool isFoodInDream();

bool CheckCollision_snake_obstacle();
bool CheckCollision_snake_portal();
bool CheckCollision_snake_monster();
bool CheckCollision_snake_toggleObstacle();
bool CheckCollision_food_obstacle();
bool CheckCollision_food_snake();
bool CheckCollision_food_subPortal();
bool CheckCollision_tail();
// -----------------------------------------------

// Add - remove obstacles vector and gate portal vector
void AddObstacle(int x, int y, int w, int h);

void AddPortal(int x, int y, int w, int h);

void RemoveObstacle(int x, int y);

void RemoveIceTile(int x, int y);
// ------------------------------------------------

// Map setup:
// General wall/ tile:
void wall();
void mapTile(int tile_color);

// Level mode:
void obstacle_level_1();

void obstacle_level_2();
void toggleObstacleLevel2();

void obstacle_level_3();
void movingObstalceLevel3();
void subPortalLevel3();

void mapLevel4();

void mapLevel5();


// Special mode:
void mapSpecial1();
void mapSpecial2();
// ------------------------------------------------


// Gate:
// Out:
void goOutGate_check();

void gate_out1();

void gate_out2();

void gate_out3();

void gate_out4();

void gate_open_level();
void gate_open_special();

void fake_portal_gate();

// In:
void gate_in();
void goInGate_check();
// ------------------------------------------------

// Level status:
void Level(int levelNumber);

void Level_Special(int levelNumber);


void levelClear();

void nextLevel();
// ------------------------------------------------

// Render:
void setRenderColor(int colorCode); // Color for obstacles

void RenderObstacles(); // Render obstacles
void RenderPortals(); // Render gate portals

void RenderToggleText(const std::string& text, int x, int y);
void RenderToggleObstacles_Draw_Level2();
void RenderToggleObstacles_Fill_Level2();

void RenderSubPortal();
void RenderIcePortal(); // Actually sub portal

void renderMonster();

void renderOuroboros(); // For infinity level (after level 5 and normal mode only)


void RenderFixedFood(); // Special only

void RenderIceTile();

void RenderDreamBlock(); 
// ------------------------------------------------


// Some logic for new mechanic (subPortal, ice tile, dream):
void snakeTeleport_in_to_out(std::vector<subPortal> typePortals);
void snakeTeleport_out_to_in(std::vector<subPortal> typePortals);

void iceTileLogic();

void DreamLogic();
// ------------------------------------------------