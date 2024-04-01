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
        if (!pause) loopCounter++;
        if (loopCounter > 1000) {
			loopCounter = 0;
		}
        switch (g_gameState) {
        case GameState::INTRO:
            UpdateIntroFrame();
            RenderIntro();
            if (introFinished) {
                g_gameState = GameState::MENU;
            }
            break;

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

        case GameState::LEADERBOARD:
            //HandleLeadInput();
            //loadFileScore();
            //RenderLeadScreen();
            break;

        case GameState::SKIN:
            HandleSkinInput();
            RenderSkinScreen();
            break;

        case GameState::ABOUT:
            HandleAboutInput();
            RenderAboutScreen();
            break;

        case GameState::PLAYING:
            StopBackgroundMusic();
            HandlePauseMenuInput();
            HandlePlayingInput();
            MoveSnake(running);
            foodSpawnedThisFrame = false;

            // Draw the tail on every frame
            AddTailSegment();

            movingObstalceLevel4();

            SDL_RenderClear(g_renderer);

            RenderPlaying();
            
            
            SDL_RenderPresent(g_renderer);

            if (CheckEat() && !hasEaten) {
                EatFood();
                AddTailSegment();

            }

            if (!goInGate_progress)
            if (CheckCollision() || toggleObstacleCollision()) {
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

        case GameState::ASK:
            HandleGameOver();
            RenderGameOver();
            break;

        case GameState::SAVE:
            //HandleSaveInput();
            //RenderSave();
            break;

        case GameState::OUTRO:
            RenderOutro();
            g_gameState = GameState::QUIT;
            break;

        default:
            break;
        }
        SDL_Delay(1); // Adjust delay for smoother rendering
    }
    CleanUp();
    return 0;
}