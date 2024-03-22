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

extern int snakeX;
extern int snakeY;
extern bool eaten;

extern std::vector<int> tailX;  // Snake tail segment X positions
extern std::vector<int> tailY;  // Snake tail segment Y positions
extern int tailLength;  // Length of the snake's tail
extern int lock;

extern std::deque<std::pair<int, int>> positions;
extern int a[32];
extern int pause;
void MoveSnake(bool& running);
extern bool running;
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
extern int foodWidth, foodHeight;
extern int bkWidth, bkHeight;
extern int snakeWidth, snakeHeight;
extern bool show_food;


extern const int TAIL_SPACE;

void reset();

bool CheckEat();
void EatFood();

bool CheckCollision_food_obstacle();
bool CheckCollision();
bool CheckCollision_tail();

void AddTailSegment();

void UpdateTailPosition();

void DrawTail();

void MoveSnake(bool& running);