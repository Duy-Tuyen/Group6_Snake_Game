#include "Snake.h"

Direction snakeDirection = RIGHT;
Direction lastDirection = STOP;

int snakeX = 0;
int snakeY = 0;
bool eaten;

std::vector<int> tailX;  // Snake tail segment X positions
std::vector<int> tailY;  // Snake tail segment Y positions
std::vector<bool> tailShow;  // Snake tail segment visibility
int tailLength = 5;  // Length of the snake's tail
int lock;

std::vector<Direction> moving_obstacles_direction; // Vector to store moving obstacles direction

std::deque<std::pair<int, int>> positions;
int a[32] = { 3,1,2,7,3,0,7,2,3,1,2,7,3,1,6,2,3,1,2,7,1,4,0,2,3,1,2,7,4,1,9,2 };
int pause = 0;
void MoveSnake(bool& running);
bool running = true;
bool foodSpawnedThisFrame = false;
bool lockMovement = false;
bool lockDir = false;

int tailDelayCounter = 0;
const int TAIL_DELAY = 5;
int PIXEL_PER_LOOP = 16; // Adjust the speed as needed
int loopDelay = 120; // Adjust the delay for smoother movement
int FOOD_TO_EAT = 5; // Number of food items to eat to pass the level
const int MAX_LEVEL = 3; // Maximum number of levels in the game
int foodEaten = 0; // Number of food items eaten by the snake
bool hasEaten = false;


int foodX = 0;
int foodY = 0;
int foodWidth_png, foodHeight_png;
int bkWidth, bkHeight;
int snakeWidth_png, snakeHeight_png;
float snakeScale = 1, foodScale = 1;
int foodWidth, foodHeight;
int snakeWidth, snakeHeight;
bool show_food = true;


const int TAIL_SPACE = 16;

void spawnFood() {
    if (!specialMode) {
        int x_16pixel_range = 38;
        int y_16pixel_range = 26;
        int x_index;
        int y_index;
        if (currentLevel == 4) {
            do {
                x_index = rand() % x_16pixel_range;
                y_index = rand() % y_16pixel_range;
                foodX = PLAY_AREA_LEFT + 16 * x_index;
                foodY = PLAY_AREA_TOP + 16 * y_index;
            } while (CheckCollision_food_obstacle() || CheckCollision_food_snake() || CheckCollision_food_subPortal() || (foodX >= PLAY_AREA_RIGHT - 16 * 8 && foodY >= PLAY_AREA_TOP + 16 * 13));
        }
        else {
            do {
				x_index = rand() % x_16pixel_range;
				y_index = rand() % y_16pixel_range;
				foodX = PLAY_AREA_LEFT + 16 * x_index;
				foodY = PLAY_AREA_TOP + 16 * y_index;
			} while (CheckCollision_food_obstacle() || CheckCollision_food_snake() || CheckCollision_food_subPortal() || isFoodInDream());
		}
    }
}

void reset() {
    snakeX = 0;
    snakeY = 0;
    snakeDirection = RIGHT; // Reset snake direction
    lastDirection = RIGHT; // Reset last direction

    levelClear();

    // Reset any other game state variables as needed
    //
    foodEaten = 0;
    foodCount = 0;
    g_statsBars = nullptr;

    if (specialMode) {
        
        Level_Special(currentLevel);
    }
    else {
        Level(currentLevel);

        show_food = true;


        g_food = LoadTexture("Food.png");
        ApplyTexture2(g_food, foodX - foodWidth / 2, foodY - foodHeight / 2, foodWidth, foodHeight);
    }
    goOutGate_progress = true;
    gate_open_step[0] = true;
}

bool CheckEat_Level() {
    // Calculate the distance between the snake and the food
    int distanceX = abs(snakeX - foodX);
    int distanceY = abs(snakeY - foodY);
    int edgeDistanceX = (snakeWidth + foodWidth) / 2;
    int edgeDistanceY = (snakeHeight + foodHeight) / 2;

    // If the snake is close enough to the food, consider it a collision
    return (!foodSpawnedThisFrame && distanceX < edgeDistanceX && distanceY < edgeDistanceY);
}

void EatFood_Level() {
    // Check if the snake has collided with the food
    if (CheckEat_Level() && !hasEaten) {
        hasEaten = true;
        PlayScoreMusic();
        UpdateStats();
        UpdateStatsBar();
        // Increase the tail length
        tailLength++;


        foodSpawnedThisFrame = true;

        SDL_DestroyTexture(g_food);
        g_food = LoadTexture("Food.png");
        spawnFood();
        ApplyTexture2(g_food, foodX - foodWidth / 2, foodY - foodHeight / 2, foodWidth, foodHeight);

    }

    foodEaten++;
    if (foodEaten == FOOD_TO_EAT && currentLevel < 6) {
        gate_in();
        SDL_DestroyTexture(g_food);
        foodX = 960;
        foodY = 540;
        show_food = false;

    }

    // Reset hasEaten to false after the new food is spawned
    hasEaten = false;
}

void EatFood_Special() {
    for (int i = 0; i < fixedFood.size(); i++) {
        // Calculate the distance between the snake and the food
        int distanceX = abs(snakeX - fixedFood[i].x);
        int distanceY = abs(snakeY - fixedFood[i].y);
        int edgeDistanceX = 16;
        int edgeDistanceY = 16;

        if (distanceX < edgeDistanceX && distanceY < edgeDistanceY) {
            AddTailSegment();
			PlayScoreMusic();

            tailLength++;
			foodEaten++;
			UpdateStats();
			UpdateStatsBar();
            fixedFood.erase(fixedFood.begin() + i);
			break;
		}
    }

    if (foodEaten == FOOD_TO_EAT) {
        gate_in();

    }
}


void AddTailSegment() {

    if (tailLength > tailX.size() && !pause) {
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
            newTailY += snakeHeight;
            break;
        case DOWN:
            newTailY -= snakeHeight;
            break;
        case LEFT:
            newTailX += snakeWidth;
            break;
        case RIGHT:
            newTailX -= snakeWidth;
            break;
        }

        tailX.push_back(newTailX);
        tailY.push_back(newTailY);
        tailShow.push_back(true);
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
        if (tailShow[i]) {
            std::string filePath = std::to_string(a[i % 32]) + ".png";


            SDL_Texture* numberTexture = LoadTexture(filePath);

            if (isInDream(tailX[i], tailY[i])) {
                numberTexture = LoadTexture("0.png");
            }

            if (numberTexture != nullptr) {
                ApplyTexture2(numberTexture, tailX[i] - snakeWidth / 2, tailY[i] - snakeHeight / 2, snakeWidth, snakeHeight);

            }
            else {
                std::cout << "Failed";
            }
        }
    }
}

int prevX;
int prevY;
void MoveSnake(bool& running) {
    if (!pause) {
        // Store the previous position of the snake's head
        prevX = snakeX;
        prevY = snakeY;
        positions.push_front({ snakeX, snakeY });
    }

    
    if (!lockMovement) {
        // Update the position of the snake's head based on the direction
        switch (snakeDirection) {
        case UP:
            if (lastDirection != DOWN) {
                if (snakeY > PLAY_AREA_TOP) {
                    pause = 0;
                    snakeY -= PIXEL_PER_LOOP;
                    lastDirection = UP;
                }
            }
            else {
                if (snakeY < PLAY_AREA_BOTTOM) {
                    if (pause) break;
                    snakeY += PIXEL_PER_LOOP;
                    lastDirection = DOWN;
                }
            }
            break;
        case DOWN:
            if (lastDirection != UP) {
                if (snakeY < PLAY_AREA_BOTTOM) {
                    pause = 0;
                    snakeY += PIXEL_PER_LOOP;
                    lastDirection = DOWN;
                }
            }
            else {
                if (snakeY > PLAY_AREA_TOP) {
                    if (pause) break;
                    snakeY -= PIXEL_PER_LOOP;
                    lastDirection = UP;
                }
            }
            break;
        case LEFT:
            if (lastDirection != RIGHT) {
                if (snakeX > PLAY_AREA_LEFT) {
                    pause = 0;
                    snakeX -= PIXEL_PER_LOOP;
                    lastDirection = LEFT;
                }
            }
            else {
                if (snakeX < PLAY_AREA_RIGHT) {
                    if (pause) break;
                    snakeX += PIXEL_PER_LOOP;
                    lastDirection = RIGHT;
                }
            }
            break;
        case RIGHT:
            if (lastDirection != LEFT) {
                if (snakeX < PLAY_AREA_RIGHT) {
                    pause = 0;
                    snakeX += PIXEL_PER_LOOP;
                    lastDirection = RIGHT;
                }
            }
            else {
                if (snakeX > PLAY_AREA_LEFT) {
                    if (pause) break;
                    snakeX -= PIXEL_PER_LOOP;
                    lastDirection = LEFT;
                }
            }
            break;

        case PAUSE:
            if (pause == 0) {
                pause = 1;
            }
            break;
        }
    }
    

    if (positions.size() > tailX.size()) {
        positions.pop_back();
    }

    if (!pause) {

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

    snakeTeleport_in_to_out(subPortals);
    snakeTeleport_out_to_in(subPortals);

    snakeTeleport_in_to_out(icePortals);
    snakeTeleport_out_to_in(icePortals);
}

void RenderPlayingSkin() {
    switch (currentColorIndex) {
    case 0: // green
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 0);
        break;
    case 1: // red
        SDL_SetRenderDrawColor(g_renderer, 255, 90, 90, 0);
		break;
    case 2: // blue
		SDL_SetRenderDrawColor(g_renderer, 0, 204, 255, 0);
		break;
    case 3: // orange
        SDL_SetRenderDrawColor(g_renderer, 255, 165, 0, 0);
        break;
    case 4: // pink
        SDL_SetRenderDrawColor(g_renderer, 255, 105, 180, 0);
		break;
    }

    SDL_Rect snakeRect = { snakeX - snakeWidth / 2, snakeY - snakeHeight / 2, snakeWidth, snakeHeight };
	SDL_RenderFillRect(g_renderer, &snakeRect);

    for (int i = 0; i < tailX.size(); i++) {
        if (tailShow[i]) {
            SDL_Rect tailRect = { tailX[i] - snakeWidth / 2, tailY[i] - snakeHeight / 2, snakeWidth, snakeHeight };
            SDL_RenderFillRect(g_renderer, &tailRect);
        }
    }

}