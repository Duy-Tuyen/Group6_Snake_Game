#pragma once
#include "Snake.h"

#include <iostream>
#include <thread>
#include "Windows.h"
#include <vector>
#include <deque>


#include "Level.h"
#include "Graphics.h"

enum Direction { STOP, UP, DOWN, LEFT, RIGHT, PAUSE };
extern Direction snakeDirection;
extern Direction lastDirection;

extern std::vector<Direction> moving_obstacles_direction; // Vector to store moving obstacles direction

extern int snakeX;
extern int snakeY;
extern bool eaten;

extern std::vector<int> tailX;  // Snake tail segment X positions
extern std::vector<int> tailY;  // Snake tail segment Y positions
extern std::vector<bool> tailShow;  // Snake tail segment visibility
extern int tailLength;  // Length of the snake's tail
extern int lock;

extern std::deque<std::pair<int, int>> positions;
extern int a[32];
extern int pause;
void MoveSnake(bool& running);
extern bool running;
extern bool lockMovement;
extern bool lockDir;
extern bool foodSpawnedThisFrame;

extern int tailDelayCounter;
extern const int TAIL_DELAY;
extern int SNAKE_SPEED; // Adjust the speed as needed
extern int FOOD_TO_EAT; // Number of food items to eat to pass the level
extern const int MAX_LEVEL; // Maximum number of levels in the game
extern int foodEaten; // Number of food items eaten by the snake
extern bool hasEaten;


extern int foodX;
extern int foodY;
extern int foodWidth_png, foodHeight_png;
extern int snakeWidth_png, snakeHeight_png;
extern float snakeScale, foodScale;
extern int foodWidth, foodHeight;
extern int snakeWidth, snakeHeight;
extern int bkWidth, bkHeight;
extern bool show_food;

extern const int TAIL_SPACE;

void spawnFood();

void reset();

bool CheckEat();
void EatFood();

bool CheckCollision_food_obstacle();
bool CheckCollision_food_snake();
bool CheckCollision();
bool CheckCollision_tail();

void AddTailSegment();

void UpdateTailPosition();

void DrawTail();

void MoveSnake(bool& running);

void RenderPlaying_LevelSkin();