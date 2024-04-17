#include "Snake.h"
#include "Level.h"
#include "Graphics.h"

int main(int argc, char** argv) {
    if (!Init()) {
        return 1;
    }

    // Play background music when rendering the menu
    PlayBackgroundMusic();

    while (g_gameState != GameState::QUIT && running) {
        setZoom(zoom_scale);
        if (!pause && !goOutGate_progress) loopCounter++;
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
            RenderMenuAnimation();
            // RenderSnakeMenu();
            SDL_Delay(80);
            break;

        case GameState::LOAD:
            loadFileScore();
            HandleLoadInput();
            RenderLoadScreen();
            break;

        case GameState::SETTINGS:
            HandleSettingsInput();
            RenderSettingsScreen();
            break;

        case GameState::LEADERBOARD:
            HandleLeadInput();
            loadFileScore();
            RenderLeadScreen();
            break;

        case GameState::SKIN:
            HandleSkinInput();
            RenderSkinScreen();
            break;

        case GameState::GUIDE:
            HandleGuideInput();
            RenderGuideAnimation();
            SDL_Delay(80);
            break;

        case GameState::ABOUT:
            HandleAboutInput();
            RenderAboutScreen();
            break;

        case GameState::MODE:
            HandleModeInput();
            RenderModeScreen();
            break;

        case GameState::PLAYING:
            StopBackgroundMusic();
            PlayLevelMusic();

            setupAndQuery_Level();

            HandlePauseMenuInput();
            HandlePlayingInput();
            MoveSnake(running);
            foodSpawnedThisFrame = false;

            AddTailSegment();

            movingObstalceLevel3();
            if (!continueGame) {
                RenderPlaying_Level();
                SDL_RenderPresent(g_renderer);
            }
            else {
				continueGame = false;
			}
            

            if (gate_open_step[0]) {
                SDL_DestroyTexture(g_snake);
                snakeX = 0;
                snakeY = 0;
                for (int i = 0; i < tailX.size(); i++) {
                    tailX[i] = 0;
                    tailY[i] = 0;
                    tailShow[i] = false;
                }

                spawnFood();
                
                lockMovement = true;
                goOutGate_progress = true;
            }
            if (gate_open_step[0] || gate_open_step[1] || gate_open_step[2] || gate_open_step[3]) {
                gate_open_level();
                SDL_Delay(100);
                continue;
            }
            
            SDL_RenderClear(g_renderer);

            if (CheckEat_Level() && !hasEaten) {
                EatFood_Level();
                AddTailSegment();

            }

            if (CheckCollision_snake_toggleObstacle()) {
                PlayHurtMusic();
                g_gameState = GameState::ASK;
            }
            
            if (CheckCollision_snake_obstacle()) {
                PlayHurtMusic();
                g_gameState = GameState::ASK;
            }
            if (CheckCollision_tail()) {
                PlayHurtMusic();
                g_gameState = GameState::ASK;
            }

            if (CheckCollision_snake_monster()) {
                PlayHurtMusic();
                g_gameState = GameState::ASK;
			}

            goInGate_check();
            goOutGate_check();

            trueDelay = (speed == 1) ? loopDelay : (speed == 2) ? (int)(loopDelay / 1.5) : (int)(loopDelay / 2);
            SDL_Delay(trueDelay); // Adjust delay for smoother movement
            break;

        case GameState::SPECIAL:
            StopBackgroundMusic();
            PlayLevelMusic();

            if (currentLevel == 3) {
                continueGame = true;
                StopBackgroundMusic();
                PlayBackgroundMusic();

                while (tailX.size() > 5) {
                    tailX.pop_back();
                    tailY.pop_back();
                    snakeLength--;
                    tailLength--;
                }

                for (int i = 0; i < positions.size(); i++) {
                    positions[i] = { 0, 0 };
                }

                isPlaying = false;
                levelClear();
                currentLevel = 1;
                specialMode = false;
                setupForLevel = true;
                setupForSpecial = true;
                g_gameState = GameState::WINNING;
                break;
            }

            setupAndQuery_Special();

            HandlePauseMenuInput();
            HandlePlayingInput();
            MoveSnake(running);

            AddTailSegment();

            if (!continueGame) {
                RenderPlaying_Special();
                SDL_RenderPresent(g_renderer);
            }
            else {
				continueGame = false;
			}

            if (gate_open_step[0]) {
                SDL_DestroyTexture(g_snake);
                snakeX = 0;
                snakeY = 0;
                for (int i = 0; i < tailX.size(); i++) {
                    tailX[i] = 0;
                    tailY[i] = 0;
                    tailShow[i] = false;
                }

                lockMovement = true;
                goOutGate_progress = true;
            }
            if (gate_open_step[0] || gate_open_step[1] || gate_open_step[2] || gate_open_step[3]) {
                gate_open_special();
                SDL_Delay(100);
                continue;
            }

            SDL_RenderClear(g_renderer);

            EatFood_Special();

            if (CheckCollision_snake_toggleObstacle()) {
                PlayHurtMusic();
                g_gameState = GameState::ASK;
            }

            if (CheckCollision_snake_obstacle()) {
                PlayHurtMusic();
                g_gameState = GameState::ASK;
                //running = false;
            }
            if (CheckCollision_tail()) {
                PlayHurtMusic();
                g_gameState = GameState::ASK;
            }

            goInGate_check();
            goOutGate_check();

            trueDelay = (speed == 1) ? loopDelay : (speed == 2) ? (int)(loopDelay / 1.5) : (int)(loopDelay / 2);
            SDL_Delay(trueDelay); // Adjust delay for smoother movement
            break;

        case GameState::WINNING:
            HandleWinning();
			RenderWinningScreen();
			break;

        case GameState::ASK:
            HandleGameOver();
            RenderGameOver();
            break;

        case GameState::SAVE:
            HandleSaveInput();
            RenderSave();
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