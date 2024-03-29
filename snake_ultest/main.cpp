#include "Snake.h"
#include "Level.h"
#include "Graphics.h"

int main(int argc, char** argv) {
    if (!Init()) {
        return 1;
    }

    setupAndQuery();

    while (g_gameState != GameState::QUIT && running) {
        loopCounter++;
        if (loopCounter > 1000) {
			loopCounter = 0;
		}
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

            movingObstalceLevel4();

            SDL_RenderClear(g_renderer);
            // Draw the tail on every frame
            RenderPlaying();
            
            
            SDL_RenderPresent(g_renderer);


            if (CheckEat() && !hasEaten) {
                EatFood();
                AddTailSegment();

            }

            if (!goInGate_progress)
            if (CheckCollision() == true || toggleObstacleCollision()) {
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
        SDL_Delay(1); // Adjust delay for smoother rendering
    }
    CleanUp();
    return 0;
}