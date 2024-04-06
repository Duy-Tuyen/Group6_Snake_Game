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
    INTRO,
    MENU,
    LOAD,
    SETTINGS,
    LEADERBOARD,
    SKIN,
    ABOUT,
    TIMER,
    PLAYING,
    ASK,
    SAVE,
    QUIT,
    OUTRO,
    SPECIAL,
    MODE
};

extern int loopCounter;

extern SDL_Window* g_window;

extern SDL_Renderer* g_renderer;

extern SDL_Texture* g_bkground;
extern SDL_Texture* g_menuBackground;
extern SDL_Texture* g_aboutUs;
extern SDL_Texture* g_loadGame;
extern SDL_Texture* g_settings;

extern SDL_Texture* g_mode;

extern SDL_Texture* g_snake;
extern SDL_Texture* g_food;
extern SDL_Texture* g_statsBars;

extern SDL_Texture* g_timer;
extern SDL_Texture* g_quit;

extern SDL_Texture* g_returnButton;
extern SDL_Texture* g_soundOnButton;
extern SDL_Texture* g_soundOffButton;

extern SDL_Texture* g_skinButton;
extern SDL_Texture* g_skinBackground;
extern SDL_Texture* g_speedBars;
extern SDL_Texture* g_colorSkin;
extern SDL_Texture* g_colorSnake;
extern SDL_Texture* g_intro;
extern SDL_Texture* g_outro;

extern SDL_Texture* g_subPortal;
extern SDL_Texture* g_icePortal;

extern SDL_Texture* g_pauseMenu;

extern SDL_Texture* g_monster1;
extern SDL_Texture* g_monster2;

// Texture for special mode
extern SDL_Texture* g_iceTile;

extern Mix_Music* g_backgroundMusic;
extern Mix_Music* g_levelMusic;
extern Mix_Chunk* g_scoreMusic;
extern Mix_Chunk* g_hurtMusic;
extern Mix_Music* g_countMusic;

extern SDL_Event g_event;
extern GameState g_gameState;

extern const int RETURN_BUTTON_X;
extern const int RETURN_BUTTON_Y;
extern const int SOUND_ON_BUTTON_X;
extern const int SOUND_ON_BUTTON_Y;
extern const int SOUND_OFF_BUTTON_X;
extern const int SOUND_OFF_BUTTON_Y;
extern const int SKIN_BUTTON_X;
extern const int SKIN_BUTTON_Y;

extern int speed;
extern const int minSpeed;
extern const int maxSpeed;

// Level statistics
extern int level;
extern int foodCount;
extern int snakeLength;
extern int score;
extern int foodBarWidth, foodBarHeight;
extern int pauseMenuWidth, pauseMenuHeight;

extern bool setupForLevel;
extern bool setupForSpecial;

extern bool specialMode;

// Font for rendering text
extern TTF_Font* g_font;

// Define variables for color animation
extern int currentFrame;
extern const int NUM_COLOR_FRAMES;
extern int COLOR_FRAME_RATE;
extern int INTRO_FRAME_RATE;
extern const int MAX_COLOR_FRAME_RATE;
extern const int MIN_COLOR_FRAME_RATE;
extern const int FRAME_RATE_INCREMENT;

extern const int frameWidth;
extern const int frameHeight;

// Define variables for color switch
extern int currentColorIndex;
extern const int NUM_COLORS;
extern std::vector<std::string> colorFileName; // File names for different colors

extern const int TIMER_DURATION_SECONDS;
extern const int NUM_TIMER_FRAMES;
extern const int NUM_INTRO_FRAMES;
extern bool introFinished;
extern int currentIntroFrame;
// Define variables for timer
extern int currentTimerFrame;


bool Init();

SDL_Texture* LoadTexture(std::string filepath);

void ApplyTexture1(SDL_Texture* texture, int x, int y);
void ApplyTexture2(SDL_Texture* texture, int x, int y, int width, int height);

void CleanUp();

bool IsPointInRect(int x, int y, const SDL_Rect& rect);

void PlayBackgroundMusic();

// Stop background music
void StopBackgroundMusic();

void PlayMenuBackgroundMusic();

void PlayLevelMusic();

void PlayScoreMusic();

void PlayHurtMusic();

void PlayCountMusic();

extern bool currStop;
extern bool isPlaying;

void HandleReturnButtonInput();
void HandleSoundOnButtonInput();
void HandleSoundOffButtonInput();


void HandleReturnButtonSkinInput();

void UpdateCount(int timerValue);

void UpdateTimer();

void RenderCount();

void HandleTimerEvent();

void UpdateIntroFrame();

void RenderIntro();

void RenderOutro();

void RenderSkinSpeedScreen();

void RenderSkinAnimation(SDL_Renderer* renderer, SDL_Texture* spriteSheet, int frameWidth, int frameHeight, int NUM_COLOR_FRAMES, int numRows, int currentFrame, int x, int y, int sheetWidth, int sheetHeight);

void UpdateColorAnimationFrame();

void UpdateSnakeColor();

void RenderColorAnimation();

void RenderSkinScreen();

void HandleSkinInput();

void HandleSkinButtonInput();


void HandleMenuInput();
void HandleLoadInput();
void HandleSettingsInput();
void HandleAboutInput();
void HandleQuitInput();
void HandlePlayingInput();

void HandleModeInput();

void RenderModeScreen();


void UpdateStats();
void UpdateStatsBar();


void RenderText(const std::string& text, int x, int y);


void RenderLevelStats();

void RenderMenu();

void RenderLoadScreen();

void RenderSettingsScreen();

void RenderAboutScreen();

void RenderQuitScreen();

void RenderPlaying_Level();
void RenderPlaying_Special();

void setupAndQuery_Level();
void setupAndQuery_Special();

void RenderPauseMenu();
void HandlePauseMenuInput();
void HandleContinueButtonInput();

void HandleTimer();

void HandleGameOver();

void RenderGameOver();

//void HandleSaveInput();

//void RenderSave();

//void HandleLeadInput();

//void RenderLeadScreen();

void setZoom(float zoom);

extern float zoom_scale;
