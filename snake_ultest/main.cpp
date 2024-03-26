#include "Snake.h"
#include "Level.h"
#include "Graphics.h"

int main(int argc, char** argv) {
    if (!Init()) {
        return 1;
    }

    setupAndQuery();

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

            AddTailSegment();

            SDL_RenderClear(g_renderer);
            // Draw the tail on every frame
            RenderPlaying();
            
            
            SDL_RenderPresent(g_renderer);


            if (CheckEat() && !hasEaten) {
                EatFood();
                AddTailSegment();

            }

            if (!goInGate_progress)
            if (CheckCollision() == true) {
                //running = false;
            }

            if (CheckCollisionWithObstacles(snakeX, snakeY, 16, 16)) {
                PlayHurtMusic();
                //running = false;
            }
            if (CheckCollision_tail()) {
                //running = false;
            }

            goInGate_check();
            goOutGate_check();

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