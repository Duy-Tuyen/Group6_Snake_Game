#pragma once
#include <iostream>
#include <string>
#include <thread>
#include "Windows.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <deque>

#include "Level.h"
#include "Snake.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// Enum to represent different game states
enum class GameState {
    MENU,
    LOAD,
    SETTINGS,
    ABOUT,
    PLAYING,
    QUIT
};

extern int loopCounter;

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Texture* g_bkground;
extern SDL_Texture* g_snake;
extern SDL_Texture* g_food;
extern SDL_Texture* g_statsBars; // Array to hold textures for six stats bars
extern SDL_Texture* g_menuBackground;
extern SDL_Texture* g_aboutUs;
extern SDL_Texture* g_loadGame;
extern SDL_Texture* g_settings;
extern SDL_Texture* g_quit;
extern SDL_Texture* g_returnButton;
extern SDL_Texture* g_soundOnButton;
extern SDL_Texture* g_soundOffButton;
extern SDL_Texture* g_pauseMenu;
extern SDL_Texture* g_monster1;
extern SDL_Texture* g_monster2;
extern SDL_Texture* g_specialFood;
extern Mix_Music* g_backgroundMusic;
extern Mix_Music* g_scoreMusic;
extern Mix_Music* g_hurtMusic;

extern SDL_Event g_event;
extern GameState g_gameState;

extern const int RETURN_BUTTON_X;
extern const int RETURN_BUTTON_Y;
extern const int SOUND_ON_BUTTON_X;
extern const int SOUND_ON_BUTTON_Y;
extern const int SOUND_OFF_BUTTON_X;
extern const int SOUND_OFF_BUTTON_Y;

// Level statistics
extern int level;
extern int foodCount;
extern int snakeLength;
extern int score;
// Font for rendering text
extern TTF_Font* g_font;
SDL_Texture* LoadTexture(std::string filepath);


bool Init();
void ApplyTexture1(SDL_Texture* texture, int x, int y);
void ApplyTexture2(SDL_Texture* texture, int x, int y, int width, int height);

void CleanUp();

bool IsPointInRect(int x, int y, const SDL_Rect& rect);

void PlayBackgroundMusic();

// Stop background music
void StopBackgroundMusic();

void PlayMenuBackgroundMusic();

void PlayScoreMusic();

void PlayHurtMusic();

void HandleReturnButtonInput();
void HandleSoundOnButtonInput();
void HandleSoundOffButtonInput();

void HandleMenuInput();

void HandleLoadInput();
void HandleSettingsInput();


void HandleAboutInput();

void HandleQuitInput();


void HandlePlayingInput();

void UpdateStats();

void UpdateStatsBar();


void RenderText(const std::string& text, int x, int y);


void RenderLevelStats();

void RenderMenu();

void RenderLoadScreen();

void RenderSettingsScreen();

void RenderAboutScreen();

void RenderQuitScreen();

void RenderPlaying();

void setupAndQuery();

void RenderPauseMenu();
void HandlePauseMenuInput();
void HandleContinueButtonInput();
