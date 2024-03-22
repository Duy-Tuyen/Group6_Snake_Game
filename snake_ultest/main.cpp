#include "Snake.h"
#include "Level.h"
#include "Graphics.h"

int main(int argc, char** argv) {
    if (!Init()) {
        return 1;
    }
    // Initialize obstacles
    Level(1);

    // Play background music when rendering the menu
    PlayBackgroundMusic();
    while (g_gameState != GameState::QUIT && running) {
        switch (g_gameState) {
        case GameState::MENU:
            HandleMenuInput();
            RenderMenu();
            break;
        case GameState::LOAD:
            HandleLoadInput();
            RenderLoadScreen();
            break;
        case GameState::SETTINGS:
            HandleSettingsInput();
            RenderSettingsScreen();
            break;
        case GameState::ABOUT:
            HandleAboutInput();
            RenderAboutScreen();
            break;
        case GameState::PLAYING:
            StopBackgroundMusic();
            HandlePlayingInput();
            MoveSnake(running);
            foodSpawnedThisFrame = false;

            // Update the tail position on every frame
            if (!tailX.empty() && !tailY.empty()) {
                UpdateTailPosition();
            }

            SDL_RenderClear(g_renderer);
            // Draw the tail on every frame

            RenderPlaying();
            DrawTail();
            RenderObstacles(g_renderer);
            RenderPortals(g_renderer);
            SDL_RenderPresent(g_renderer);


            if (CheckEat() && !hasEaten) {
                EatFood();
                AddTailSegment();

            }

            if (CheckCollision() == true) {
                //running = false;
            }

            if (CheckCollisionWithObstacles(snakeX, snakeY, 20, 20)) {
                PlayHurtMusic();
                //running = false;
            }
            if (CheckCollision_tail()) {
                //running = false;
            }

            if (CheckCollisionWithPortals(snakeX, snakeY, 20, 20)) {
                nextLevel();
            }

            SDL_Delay(100); // Adjust delay for smoother movement
            break;
        default:
            break;
        }
        SDL_Delay(10); // Adjust delay for smoother rendering
    }
    CleanUp();
    return 0;
}