#include "Snake.h"

Direction snakeDirection = RIGHT;
Direction lastDirection = STOP;

int snakeX = 200;
int snakeY = 270;
bool eaten;

std::vector<int> tailX;  // Snake tail segment X positions
std::vector<int> tailY;  // Snake tail segment Y positions
int tailLength = 5;  // Length of the snake's tail
int lock;

std::deque<std::pair<int, int>> positions;
int a[32] = { 3,1,2,7,3,0,7,2,3,1,2,7,3,1,6,2,3,1,2,7,1,4,0,2,3,1,2,7,4,1,9 };
int pause = 0;
void MoveSnake(bool& running);
bool running = true;
bool foodSpawnedThisFrame = false;

int tailDelayCounter = 0;
const int TAIL_DELAY = 5;
int SNAKE_SPEED = 20; // Adjust the speed as needed
int FOOD_TO_EAT = 5; // Number of food items to eat to pass the level
const int MAX_LEVEL = 3; // Maximum number of levels in the game
int foodEaten = 0; // Number of food items eaten by the snake
bool hasEaten = false;


int foodX = rand () % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 + 2 * foodWidth * 2) + PLAY_AREA_LEFT + foodWidth * 2;
int foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 + 2 * foodHeight * 2) + PLAY_AREA_TOP + foodHeight * 2;
int foodWidth, foodHeight;
int bkWidth, bkHeight;
int snakeWidth, snakeHeight;
bool show_food = true;


const int TAIL_SPACE = 35;

void reset() {
    // Reset snake position
    snakeX = 200; // Reset snake X position
    snakeY = 270; // Reset snake Y position
    snakeDirection = RIGHT; // Reset snake direction
    lastDirection = RIGHT; // Reset last direction

    

        do {
            foodX = rand() % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 - 2 * foodWidth * 2) + PLAY_AREA_LEFT + foodWidth * 2;
            foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 - 2 * foodHeight * 2) + PLAY_AREA_TOP + foodHeight * 2;
        } while (CheckCollision_food_obstacle());
    show_food = true;

    foodEaten = 0;
    foodCount = 0;
    g_statsBars = nullptr;

    // Remove all obstacles
    obstacles.clear();

    // Remove all portals
    portals.clear();

    // Reset any other game state variables as needed
}

bool CheckEat() {
    // Calculate the distance between the snake and the food
    int distanceX = abs(snakeX - foodX);
    int distanceY = abs(snakeY - foodY);

    // If the snake is close enough to the food, consider it a collision
    return (!foodSpawnedThisFrame && distanceX < foodWidth && distanceY < foodHeight);
}

bool CheckCollision_food_obstacle() {
    for (int i = 0; i < obstacles.size(); i++) {
        int distanceX = abs(foodX - obstacles[i].x);
        int distanceY = abs(foodY - obstacles[i].y);
        if (distanceX < foodWidth + 20 && distanceY < foodHeight + 20) {
            std::cout << "Collision with obstacle\n";
            return true;
        }
    }
    return false;
}

void EatFood() {
    // Check if the snake has collided with the food
    if (CheckEat() && !hasEaten) {
        hasEaten = true;
        PlayScoreMusic();
        UpdateStats();
        UpdateStatsBar();
        // Increase the tail length
        tailLength++;


        foodSpawnedThisFrame = true;

            do {
                SDL_DestroyTexture(g_food);
                g_food = LoadTexture("Food.png");
                foodX = rand() % (PLAY_AREA_RIGHT - PLAY_AREA_LEFT + 1 - 2 * foodWidth * 2) + PLAY_AREA_LEFT + foodWidth * 2;
                foodY = rand() % (PLAY_AREA_BOTTOM - PLAY_AREA_TOP + 1 - 2 * foodHeight * 2) + PLAY_AREA_TOP + foodHeight * 2;
                ApplyTexture2(g_food, foodX, foodY, foodWidth * 2, foodHeight * 2);
            } while (CheckCollision_food_obstacle());

        foodEaten++;
        if (foodEaten == FOOD_TO_EAT) {
            gate();
            SDL_DestroyTexture(g_food);
            foodX = 0;
            foodY = 0;
            show_food = false;

        }

        // Reset hasEaten to false after the new food is spawned
        hasEaten = false;
    }
}

bool CheckCollision_tail() {
	for (int i = 0; i < tailX.size(); i++) {
		int distanceX = abs(snakeX - tailX[i]);
        int distanceY = abs(snakeY - tailY[i]);
    if (distanceX < snakeWidth && distanceY < snakeHeight) {
        std::cout << "Collision with tail\n";
        return true;
        }
    }
	return false;
}

bool CheckCollision() {
    //Check collision with the boundaries of the play area
    if (snakeX < PLAY_AREA_LEFT || snakeX >= PLAY_AREA_RIGHT - 25 || snakeY < PLAY_AREA_TOP || snakeY >= PLAY_AREA_BOTTOM - 25) {
        return true; // Snake collided with the wall
    }

    // Add additional collision detection logic here for other game objects if needed

    return false; // No collision detected
}

void AddTailSegment() {

    if (tailLength > tailX.size()) {
        int newTailX, newTailY;

        if (tailX.empty() || tailY.empty()) {
            newTailX = snakeX;
            newTailY = snakeY;
        }
        else {
            newTailX = tailX.back();
            newTailY = tailY.back();
        }
        switch (lastDirection) {
        case UP:
            newTailY += snakeHeight * 3;
            break;
        case DOWN:
            newTailY -= snakeHeight * 3;
            break;
        case LEFT:
            newTailX += snakeWidth * 3;
            break;
        case RIGHT:
            newTailX -= snakeWidth * 3;
            break;
        }


        tailX.push_back(newTailX);
        tailY.push_back(newTailY);
    }
}

void UpdateTailPosition() {

    for (size_t i = tailX.size() - 1; i > 0; --i) {

        float distanceX = tailX[i - 1] - tailX[i];
        float distanceY = tailY[i - 1] - tailY[i];
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);


        float dx = distanceX / distance;
        float dy = distanceY / distance;


        tailX[i] = static_cast<int>(tailX[i - 1] - dx * TAIL_SPACE);
        tailY[i] = static_cast<int>(tailY[i - 1] - dy * TAIL_SPACE);
    }


    if (!tailX.empty() && !tailY.empty()) {

        float distanceX = snakeX - tailX[0];
        float distanceY = snakeY - tailY[0];
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);


        float dx = distanceX / distance;
        float dy = distanceY / distance;


        tailX[0] = static_cast<int>(snakeX - dx * TAIL_SPACE);
        tailY[0] = static_cast<int>(snakeY - dy * TAIL_SPACE);
    }
}

void DrawTail() {
    for (int i = 0; i < tailX.size(); i++) {

        std::string filePath = std::to_string(a[i]) + ".png";


        SDL_Texture* numberTexture = LoadTexture(filePath);

        if (numberTexture != nullptr) {

            ApplyTexture2(numberTexture, tailX[i], tailY[i], snakeWidth * 1.5, snakeHeight * 1.5);

        }
        else {
            std::cout << "Failed";
        }
    }
}

void MoveSnake(bool& running) {
    // Store the previous position of the snake's head
    int prevX = snakeX;
    int prevY = snakeY;
    positions.push_front({ snakeX, snakeY });
    // Update the position of the snake's head based on the direction
    switch (snakeDirection) {
    case UP:
        if (lastDirection != DOWN || tailLength == 5) {
            if (snakeY > PLAY_AREA_TOP) {
                snakeY -= SNAKE_SPEED;
                lastDirection = UP;
            }
        }
        else {
            if (snakeY < PLAY_AREA_BOTTOM) {
                snakeY += SNAKE_SPEED;
                lastDirection = DOWN;
            }
        }
        break;
    case DOWN:
        if (lastDirection != UP || tailLength == 5) {
            if (snakeY < PLAY_AREA_BOTTOM) {
                snakeY += SNAKE_SPEED;
                lastDirection = DOWN;
            }
        }
        else {
            if (snakeY > PLAY_AREA_TOP) {
                snakeY -= SNAKE_SPEED;
                lastDirection = UP;
            }
        }
        break;
    case LEFT:
        if (lastDirection != RIGHT || tailLength == 5) {
            if (snakeX > PLAY_AREA_LEFT) {
                snakeX -= SNAKE_SPEED;
                lastDirection = LEFT;
            }
        }
        else {
            if (snakeX < PLAY_AREA_RIGHT) {
                snakeX += SNAKE_SPEED;
                lastDirection = RIGHT;
            }
        }
        break;
    case RIGHT:
        if (lastDirection != LEFT || tailLength == 5) {
            if (snakeX < PLAY_AREA_RIGHT) {
                snakeX += SNAKE_SPEED;
                lastDirection = RIGHT;
            }
        }
        else {
            if (snakeX > PLAY_AREA_LEFT) {
                snakeX -= SNAKE_SPEED;
                lastDirection = LEFT;
            }
        }
        break;
    }
    if (positions.size() > tailX.size()) {
        positions.pop_back();
    }

    // Update the position of the tail segments to the positions stored in the deque
    for (int i = 0; i < tailX.size(); ++i) {
        tailX[i] = positions[i].first;
        tailY[i] = positions[i].second;
    }
    // Move the tail
    if (!tailX.empty() && !tailY.empty() && tailX.size() == tailY.size()) {
        // Only move the tail segments after a certain number of frames have passed
        if (tailDelayCounter >= TAIL_DELAY) {
            // Move each tail segment to the position of the segment in front of it
            for (size_t i = tailX.size() - 1; i > 0; --i) {
                tailX[i] = tailX[i - 1];
                tailY[i] = tailY[i - 1];
            }
            // Move the first tail segment to the previous position of the head
            tailX[0] = prevX;
            tailY[0] = prevY;

            // Reset the delay counter
            tailDelayCounter = 0;
        }
        else {
            // Increment the delay counter
            tailDelayCounter++;
        }
    }
}