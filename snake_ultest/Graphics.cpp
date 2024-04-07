#include "Graphics.h"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

int loopCounter = 0;

float zoom_scale = 1;

SDL_Window* g_window = nullptr;

SDL_Renderer* g_renderer = nullptr;

SDL_Texture* g_menuSnake = nullptr;

SDL_Texture* g_bkground = nullptr;
SDL_Texture* g_menuBackground = nullptr;
SDL_Texture* g_dreamBackground = nullptr;

SDL_Texture* g_loadGame = nullptr;
SDL_Texture* g_loadButton = nullptr;

SDL_Texture* g_aboutUs = nullptr;
SDL_Texture* g_settings = nullptr;

SDL_Texture* g_mode = nullptr;

SDL_Texture* g_timer;
SDL_Texture* g_quit = nullptr;

SDL_Texture* g_snake = nullptr;
SDL_Texture* g_food = nullptr;
SDL_Texture* g_statsBars = nullptr;

SDL_Texture* g_returnButton = nullptr;

SDL_Texture* g_soundOnButton = nullptr;
SDL_Texture* g_soundOffButton = nullptr;
SDL_Texture* g_MusicOption = nullptr;
SDL_Texture* g_soundOnButton1 = nullptr;
SDL_Texture* g_soundOffButton1 = nullptr;
SDL_Texture* g_soundOnButton2 = nullptr;
SDL_Texture* g_soundOffButton2 = nullptr;
SDL_Texture* g_soundOnButton3 = nullptr;
SDL_Texture* g_soundOffButton3 = nullptr;

const int MUSIC_OPTION_X = 100;
const int MUSIC_OPTION_Y = 100;
bool soundOn1 = true;
bool soundOn2 = true;
bool soundOn3 = true;



SDL_Texture* g_leaderboardButton = nullptr;
SDL_Texture* g_leaderboard = nullptr;

SDL_Texture* g_guideButton = nullptr;

SDL_Texture* g_control = nullptr;

SDL_Texture* g_skinButton = nullptr;
SDL_Texture* g_skinBackground = nullptr;
SDL_Texture* g_speedBars = nullptr;
SDL_Texture* g_colorSkin = nullptr;
SDL_Texture* g_colorSnake = nullptr;
SDL_Texture* g_intro = nullptr;
SDL_Texture* g_outro = nullptr;
SDL_Texture* g_gameOver = nullptr;
SDL_Texture* g_snakeEnter = nullptr;

SDL_Texture* g_subPortal = nullptr;
SDL_Texture* g_icePortal = nullptr;

SDL_Texture* g_pauseMenu = nullptr;

SDL_Texture* g_monster1 = nullptr;
SDL_Texture* g_monster2 = nullptr;

SDL_Texture* g_ouroboros = nullptr;


SDL_Texture* g_dreamBlock = nullptr;
SDL_Texture* g_dreamBlock1 = nullptr;

// Texture for special mode
SDL_Texture* g_iceTile = nullptr;

Mix_Music* g_backgroundMusic = nullptr;
Mix_Music* g_levelMusic = nullptr;
Mix_Chunk* g_scoreMusic = nullptr;
Mix_Chunk* g_hurtMusic = nullptr;
Mix_Music* g_countMusic = nullptr;

bool currStop = false;
bool isPlaying = false;
bool levelMusicOn = true;
bool soundEffectOn = true;

SDL_Event g_event;
GameState g_gameState = GameState::INTRO;

const int RETURN_BUTTON_X = 450;
const int RETURN_BUTTON_Y = 490;

const int SOUND_ON_BUTTON_X = 0;
const int SOUND_ON_BUTTON_Y = 110;
const int SOUND_OFF_BUTTON_X = 0;
const int SOUND_OFF_BUTTON_Y = 300;

const int SKIN_BUTTON_X = 575;
const int SKIN_BUTTON_Y = 151;
const int LEADER_BUTTON_X = 575;
const int LEADER_BUTTON_Y = 360;

const int GUIDE_BUTTON_X = 10;
const int GUIDE_BUTTON_Y = 10;

int speed = 1;
const int minSpeed = 1;
const int maxSpeed = 3;

// Level statistics
int level = 1;
int foodCount = 0;
int snakeLength = 6;
int score = 0;
int foodBarWidth, foodBarHeight;
int pauseMenuWidth, pauseMenuHeight;

bool setupForLevel = true;
bool setupForSpecial = true;

bool specialMode = false;


// Font for rendering text
TTF_Font* g_font = nullptr;

// Define variables for color animation
int currentFrame = 0;
const int NUM_COLOR_FRAMES = 3;

int COLOR_FRAME_RATE = 20;
int INTRO_FRAME_RATE = 10;
int OUTRO_FRAME_RATE = 10;
int GUIDE_FRAME_RATE = 10;
int MENU_FRAME_RATE = 10;

const int MAX_COLOR_FRAME_RATE = 60;
const int MIN_COLOR_FRAME_RATE = 20;
const int FRAME_RATE_INCREMENT = 20;

const int frameWidth = 100;
const int frameHeight = 100;

// Define variables for color switch
int currentColorIndex = 0;
const int NUM_COLORS = 5;
std::vector<std::string> colorFileNames = { "greenSnake.png", "redSnake.png", "blueSnake.png", "brownSnake.png", "pinkSnake.png" }; // File names for different colors

const int TIMER_DURATION_SECONDS = 4;
const int NUM_TIMER_FRAMES = 4;
const int NUM_INTRO_FRAMES = 6;
const int NUM_OUTRO_FRAMES = 6;
const int NUM_MENU_FRAMES = 8;
const int NUM_GUIDE_FRAMES = 7;

bool introFinished = false;
bool outroFinished = false;

int currentIntroFrame = 0;
int currentOutroFrame = 0;
int currentGuideFrame = 0;

// Define variables for timer
int currentTimerFrame = 0;



bool Init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        return false;
    }

    // Load background music
    g_backgroundMusic = Mix_LoadMUS("background_music.mp3");
    if (g_backgroundMusic == nullptr) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
        return false;
    }

    // Load Level music
    g_levelMusic = Mix_LoadMUS("playing_music.mp3");
    if (g_levelMusic == nullptr) {
		std::cerr << "Failed to load level music: " << Mix_GetError() << std::endl;
		return false;
	}

    // Load score music
    g_scoreMusic = Mix_LoadWAV("score.wav");
    if (g_scoreMusic == nullptr) {
        std::cerr << "Failed to load score music: " << Mix_GetError() << std::endl;
        return false;

    }// Load hurt music
    g_hurtMusic = Mix_LoadWAV("hurt.wav");
    if (g_hurtMusic == nullptr) {
        std::cerr << "Failed to load hurt music: " << Mix_GetError() << std::endl;
        return false;
    }

    // Load timer music
    g_countMusic = Mix_LoadMUS("countdown.wav");
    if (g_countMusic == nullptr) {
        std::cerr << "Failed to load count music: " << Mix_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        return false;
    }

    g_window = SDL_CreateWindow("Snake Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetWindowSize(g_window, SCREEN_WIDTH * zoom_scale, SCREEN_HEIGHT * zoom_scale);

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load custom TTF font
    g_font = TTF_OpenFont("ka1.ttf", 24); // Change "myfont.ttf" to your font file
    if (g_font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    // Load outro texture
    g_outro = LoadTexture("OUTRO.png");
    if (g_outro == nullptr) {
        return false;
    }


    // Load textures
    g_intro = LoadTexture("intro-display.png");
    if (g_intro == nullptr) {
        return false;
    }

    g_menuBackground = LoadTexture("menuBackground.png");
    if (g_menuBackground == nullptr) {
        return false;
    }

    g_menuSnake = LoadTexture("Snake_Animation.png");
    if (g_menuSnake == nullptr) {
        return false;
    }

    // Load game mode menu
    g_mode = LoadTexture("gameMode.png");
    if (g_mode == nullptr) {
        return false;
    }

    g_dreamBackground = LoadTexture("dreamBackground.png");
    if (g_mode == nullptr) {
        return false;
    }

    g_loadGame = LoadTexture("loadGame.png");
    if (g_loadGame == nullptr) {
        return false;
    }

    g_loadButton = LoadTexture("loadButton.png");
    if (g_loadButton == nullptr) {
        return false;
    }

    g_MusicOption = LoadTexture("Music Option.png");
    if (g_MusicOption == nullptr) {
        return false;
    }
    g_soundOnButton1 = LoadTexture("Sound On.png");
    if (g_soundOnButton1 == nullptr) {
        return false;
    }

    g_soundOffButton1 = LoadTexture("Sound Off.png");
    if (g_soundOffButton1 == nullptr) {
        return false;
    }
    g_soundOnButton2 = LoadTexture("Sound On.png");
    if (g_soundOnButton2 == nullptr) {
        return false;
    }

    g_soundOffButton2 = LoadTexture("Sound Off.png");
    if (g_soundOffButton2 == nullptr) {
        return false;
    }
    g_soundOnButton3 = LoadTexture("Sound On.png");
    if (g_soundOnButton3 == nullptr) {
        return false;
    }

    g_soundOffButton3 = LoadTexture("Sound Off.png");
    if (g_soundOffButton3 == nullptr) {
        return false;
    }


    g_returnButton = LoadTexture("returnButton.png");
    if (g_returnButton == nullptr) {
        return false;
    }

    g_soundOnButton = LoadTexture("Sound On.png");
    if (g_returnButton == nullptr) {
        return false;
    }

    g_soundOffButton = LoadTexture("Sound Off.png");
    if (g_returnButton == nullptr) {
        return false;
    }

    g_leaderboardButton = LoadTexture("leaderboardButton.png");
    if (g_leaderboardButton == nullptr) {
        return false;
    }

    g_guideButton = LoadTexture("guideButton.png");
    if (g_guideButton == nullptr) {
        return false;
    }

    g_leaderboard = LoadTexture("Leaderboard.png");
    if (g_leaderboard == nullptr) {
        return false;
    }

    g_skinButton = LoadTexture("skinButton.png");
    if (g_skinButton == nullptr) {
        return false;
    }

    g_skinBackground = LoadTexture("skinBackground.png");
    if (g_skinBackground == nullptr) {
        return false;
    }

    g_colorSkin = LoadTexture("colorSkin.png");
    if (g_colorSkin == nullptr) {
        return false;
    }

    g_aboutUs = LoadTexture("aboutUs.png");
    if (g_aboutUs == nullptr) {
        return false;
    }

    g_settings = LoadTexture("settings.png");
    if (g_settings == nullptr) {
        return false;
    }

    g_quit = LoadTexture("quit.png");
    if (g_quit == nullptr) {
        return false;
    }

    g_pauseMenu = LoadTexture("pauseMenu.png");
    if (g_pauseMenu == nullptr) {
        return false;
    }

    g_bkground = LoadTexture("playingBackground.png");
    if (g_bkground == nullptr) {
        return false;
    }

    g_snake = LoadTexture("2.png");
    if (g_snake == nullptr) {
        return false;
    }

    g_dreamBlock = LoadTexture("dreamBlock.png");
    if (g_dreamBlock == nullptr) {
        return false;
    }

    g_dreamBlock1 = LoadTexture("dreamBlock1.png");
    if (g_dreamBlock1 == nullptr) {
        return false;
    }

    g_control = LoadTexture("guide.png");
    if (g_control == nullptr) {
        return false;
    }

    g_food = LoadTexture("Food.png");
    if (g_food == nullptr) {
        return 1;
    }

    g_gameOver = LoadTexture("gameOver.png");
    if (g_food == nullptr) {
        return 1;
    }

    g_snakeEnter = LoadTexture("snakeEnter.png");
    if (g_snakeEnter == nullptr) {
        return 1;
    }


    return true;
}

SDL_Texture* LoadTexture(std::string filepath) {
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image: " << filepath << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }

    return texture;
}
void ApplyTexture1(SDL_Texture* texture, int x, int y) {
    SDL_Rect destRect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
    SDL_RenderCopy(g_renderer, texture, NULL, &destRect);
}
void ApplyTexture2(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(g_renderer, texture, NULL, &destRect);
}

void CleanUp() {
    // Free background music
    Mix_FreeMusic(g_backgroundMusic);
    Mix_FreeMusic(g_levelMusic);
    Mix_FreeChunk(g_scoreMusic);
    Mix_FreeChunk(g_hurtMusic);
    // Quit SDL_mixer
    Mix_CloseAudio();

    SDL_DestroyTexture(g_menuBackground);
    SDL_DestroyTexture(g_bkground);
    SDL_DestroyTexture(g_aboutUs);
    SDL_DestroyTexture(g_loadGame);
    SDL_DestroyTexture(g_settings);
    SDL_DestroyTexture(g_quit);

    SDL_DestroyTexture(g_skinButton);
    SDL_DestroyTexture(g_skinBackground);
    SDL_DestroyTexture(g_colorSkin);
    SDL_DestroyTexture(g_colorSnake);

    SDL_DestroyTexture(g_MusicOption);



    SDL_DestroyTexture(g_snake);
    SDL_DestroyTexture(g_statsBars);

    SDL_DestroyRenderer(g_renderer);

    SDL_DestroyWindow(g_window);

    TTF_CloseFont(g_font); // Close the font
    TTF_Quit(); // Quit SDL_ttf
}

bool IsPointInRect(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

void PlayBackgroundMusic() {
    Mix_PlayMusic(g_backgroundMusic, -1); // -1 loops the music indefinitely
}

// Stop background music
void StopBackgroundMusic() {
    if (!currStop) {
        Mix_HaltMusic();
        currStop = true;
    }
}

void PauseBackgroundMusic() {
    if (Mix_PlayingMusic() == 1) {
		Mix_PauseMusic();
	}
}

void ResumeBackgroundMusic() {
    if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
    }
}

void PlayMenuBackgroundMusic() {
    if (Mix_PlayingMusic() == 0) {
        // If no music is playing, start playing the background music
        Mix_PlayMusic(g_backgroundMusic, -1);
    }
}

void PlayLevelMusic() {
    if (!isPlaying && levelMusicOn) {
        Mix_PlayMusic(g_levelMusic, -1);
        isPlaying = true;
    }
}

void PlayCountMusic() {
    if (soundEffectOn) {
        Mix_PlayMusic(g_countMusic, 1);
    }
}


void PlayScoreMusic() {
    if (soundEffectOn) {
        Mix_PlayChannel(-1, g_scoreMusic, 0);
    }
}

void PlayHurtMusic() {
    if (soundEffectOn) {
        Mix_PlayChannel(-1, g_hurtMusic, 0);
    }
}

void HandleReturnButtonInput() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect returnButtonRect = { RETURN_BUTTON_X * zoom_scale, RETURN_BUTTON_Y * zoom_scale, 20 * zoom_scale, 20 * zoom_scale };
    if (IsPointInRect(mouseX, mouseY, returnButtonRect)) {
        g_gameState = GameState::MENU;
    }
}

void HandleReturnButtonSkinInput() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect returnButtonRect = { 880 * zoom_scale, 480 * zoom_scale, 20 * zoom_scale, 20 * zoom_scale };
    if (IsPointInRect(mouseX, mouseY, returnButtonRect)) {
        g_gameState = GameState::SETTINGS;
    }
}


void HandleSoundOnButtonInput() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOnButtonRect = { SOUND_ON_BUTTON_X * zoom_scale, SOUND_ON_BUTTON_Y * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };
    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect)) {
        PlayBackgroundMusic();
    }
}

void HandleSoundOffButtonInput() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOffButtonRect = { SOUND_OFF_BUTTON_X * zoom_scale, SOUND_OFF_BUTTON_Y * zoom_scale, 100 * zoom_scale, 300 * zoom_scale };
    if (IsPointInRect(mouseX, mouseY, soundOffButtonRect)) {
        StopBackgroundMusic();
    }
}

void HandleSoundOnButtonInput1() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOnButtonRect1 = { (SOUND_ON_BUTTON_X + 380) * zoom_scale, (SOUND_ON_BUTTON_Y + 75) * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };

    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect1) && soundOn1 == true) {
        levelMusicOn = false;
        soundOn1 = false;
        SDL_RenderPresent(g_renderer);
    }
}
void HandleSoundOffButtonInput1() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOnButtonRect1 = { (SOUND_ON_BUTTON_X + 380) * zoom_scale, (SOUND_ON_BUTTON_Y + 75) * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };


    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect1) && soundOn1 == false) {
        levelMusicOn = true;
        soundOn1 = true;
        SDL_RenderPresent(g_renderer);
    }
}
void HandleSoundOnButtonInput2() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Rect soundOnButtonRect2 = { (SOUND_ON_BUTTON_X + 380) * zoom_scale, (SOUND_ON_BUTTON_Y + 160) * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };

    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect2) && soundOn2 == true) {
        soundEffectOn = false;
        soundOn2 = false;
        SDL_RenderPresent(g_renderer);
    }
}
void HandleSoundOffButtonInput2() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOnButtonRect2 = { (SOUND_ON_BUTTON_X + 380) * zoom_scale, (SOUND_ON_BUTTON_Y + 160) * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };

    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect2) && soundOn2 == false) {
        soundEffectOn = true;
        soundOn2 = true;
        SDL_RenderPresent(g_renderer);
    }
}
void HandleSoundOnButtonInput3() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOnButtonRect3 = { (SOUND_ON_BUTTON_X + 380) * zoom_scale, (SOUND_ON_BUTTON_Y + 245) * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };

    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect3) && soundOn3 == true) {
        PauseBackgroundMusic();
        soundOn3 = false;
        SDL_RenderPresent(g_renderer);
    }
}
void HandleSoundOffButtonInput3() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOnButtonRect3 = { (SOUND_ON_BUTTON_X + 380) * zoom_scale, (SOUND_ON_BUTTON_Y + 245) * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };

    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect3) && soundOn3 == false) {
        ResumeBackgroundMusic();
        soundOn3 = true;
        SDL_RenderPresent(g_renderer);
    }
}


void UpdateTimer() {
    // Get the elapsed time since the program started
    Uint32 elapsedTime = SDL_GetTicks();

    // Calculate the duration of each timer frame in milliseconds
    Uint32 frameDuration = TIMER_DURATION_SECONDS * 1000 / NUM_TIMER_FRAMES;

    // Calculate the index of the current frame based on elapsed time and frame duration
    int currentFrameIndex = (elapsedTime / frameDuration) % NUM_TIMER_FRAMES;

    // Update the current timer frame if it has changed
    if (currentFrameIndex != currentTimerFrame) {
        currentTimerFrame = currentFrameIndex;
        UpdateCount(currentTimerFrame); // Update the timer display
    }
}



void UpdateCount(int timerFrame) {
    if (g_timer != nullptr) {
        SDL_DestroyTexture(g_timer);
        g_timer = nullptr;
    }

    std::string filePath = "Timer" + std::to_string(timerFrame) + ".png";
    g_timer = LoadTexture(filePath);
    if (g_timer == nullptr) {
        g_timer = LoadTexture("Timer0.png");
    }
}


void RenderCount() {
    SDL_RenderClear(g_renderer);
    ApplyTexture1(g_timer, 0, 0);
    SDL_RenderPresent(g_renderer);
}


// Function to handle timer events
void HandleTimerEvent() {
    // Update the countdown timer
    UpdateTimer();
    // Render the countdown timer
    RenderCount();
}

void RenderSkinSpeedScreen() {
    std::string speedText = "SPEED";
    std::string avatarText = "PICK AN AVATAR";
    std::string colorText = "COLOR";


    RenderText(speedText, 98, 4);
    RenderText(avatarText, 490, 4);
    RenderText(colorText, 50, 475);

    if (speed >= 1 && speed <= 3 && g_speedBars != nullptr) {
        ApplyTexture1(g_speedBars, 55, 41);
    }
}

void RenderSkinAnimation(SDL_Renderer* renderer, SDL_Texture* spriteSheet, int frameWidth, int frameHeight, int NUM_COLOR_FRAMES, int numRows, int currentFrame, int x, int y, int sheetWidth, int sheetHeight) {
    // Calculate the source rectangle for the current frame
    int row = currentFrame / NUM_COLOR_FRAMES;
    int col = currentFrame % NUM_COLOR_FRAMES;
    SDL_Rect srcRect;
    srcRect.x = col * frameWidth;
    srcRect.y = row * frameHeight;
    srcRect.w = frameWidth;
    srcRect.h = frameHeight;

    // Destination rectangle (where to render the frame on the screen)
    SDL_Rect destRect = { x, y, sheetWidth, sheetHeight }; // Adjusted to the entire sprite sheet size

    // Render the current frame
    SDL_RenderCopy(renderer, spriteSheet, &srcRect, &destRect);
}

// Function to update the current frame of the color animation
void UpdateColorAnimationFrame() {
    static Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - lastFrameTime;

    if (elapsedTime >= 1000 / COLOR_FRAME_RATE) {
        currentFrame++;
        if (currentFrame >= NUM_COLOR_FRAMES) {
            currentFrame = 0;
        }
        lastFrameTime = currentTime;
    }
}

void UpdateSnakeColor() {
    // Load the texture for the selected color
    if (g_colorSnake != nullptr) {
        SDL_DestroyTexture(g_colorSnake);
        g_colorSnake = nullptr;
    }
    std::string filePath = colorFileNames[currentColorIndex];
    g_colorSnake = LoadTexture(filePath);
    if (g_colorSnake == nullptr) {
        g_colorSnake = LoadTexture("greenSnake.png"); // Load default texture if loading fails
    }
}
// Function to render the color animation
void RenderColorAnimation() {
    UpdateSnakeColor();
    UpdateColorAnimationFrame();
    RenderSkinAnimation(g_renderer, g_colorSnake, frameWidth, frameHeight, NUM_COLOR_FRAMES, 1, currentFrame, 350, 0, 550, 550);
}

void UpdateIntroFrame() {
    static Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - lastFrameTime;

    if (elapsedTime >= 1000 / INTRO_FRAME_RATE) {
        // Update the current frame
        currentIntroFrame++;
        if (currentIntroFrame >= NUM_INTRO_FRAMES) {
            introFinished = true;
        }
        lastFrameTime = currentTime;
    }
}

void RenderIntroAnimation(SDL_Renderer* renderer, SDL_Texture* spriteSheet, int frameWidth, int frameHeight, int NUM_INTRO_FRAMES, int numRows, int currentFrame, int x, int y, int sheetWidth, int sheetHeight) {
    // Calculate the source rectangle for the current frame
    int row = currentFrame / NUM_INTRO_FRAMES;
    int col = currentFrame % NUM_INTRO_FRAMES;
    SDL_Rect srcRect;
    srcRect.x = col * frameWidth;
    srcRect.y = row * frameHeight;
    srcRect.w = frameWidth;
    srcRect.h = frameHeight;

    // Destination rectangle (where to render the frame on the screen)
    SDL_Rect destRect = { x, y, sheetWidth, sheetHeight }; // Adjusted to the entire sprite sheet size

    // Render the current frame
    SDL_RenderCopy(renderer, spriteSheet, &srcRect, &destRect);
}

void RenderMenuAnimation() {

    static int currentMenuFrame = 0; // Static variable to retain its value across function calls

    // Increment currentMenuFrame for next frame
    currentMenuFrame = (currentMenuFrame + 1) % NUM_MENU_FRAMES;

    // Clear the renderer
    SDL_RenderClear(g_renderer);

    // Calculate frame width and height
    int frameWidth = 496 / NUM_MENU_FRAMES;
    int frameHeight = 64;

    int row = 0;
    int col = currentMenuFrame;

    SDL_Rect srcRect;
    srcRect.x = col * frameWidth;
    srcRect.y = row * frameHeight;
    srcRect.w = frameWidth;
    srcRect.h = frameHeight;

    // Destination rectangle (where to render the frame on the screen)
    SDL_Rect destRect = { 50, 250, frameWidth * 5, frameHeight * 5 }; // Adjusted to the desired size on the screen
    SDL_Rect destRect2 = { 575, 250, frameWidth * 5, frameHeight * 5 };

    // Render the menu background
    ApplyTexture1(g_menuBackground, 0, 0);

    // Render the current frame of the snake animation
    SDL_RenderCopy(g_renderer, g_menuSnake, &srcRect, &destRect);
    SDL_RenderCopy(g_renderer, g_menuSnake, &srcRect, &destRect2);

    // Update the screen
    SDL_RenderPresent(g_renderer);
}

void RenderIntro() {
    RenderIntroAnimation(g_renderer, g_intro, 315, 250, NUM_INTRO_FRAMES, 1, currentIntroFrame, 0, 0, 960, 540);
    SDL_RenderPresent(g_renderer);
}

void UpdateOutroFrame() {

    static Uint32 lastFrameTime = SDL_GetTicks();

    Uint32 currentTime = SDL_GetTicks();

    Uint32 elapsedTime = currentTime - lastFrameTime;



    if (elapsedTime >= (1000 / OUTRO_FRAME_RATE)) {

        // Update the current frame

        currentOutroFrame++;

        if (currentOutroFrame >= NUM_OUTRO_FRAMES) {

            outroFinished = true;

        }

        lastFrameTime = currentTime;

    }

}



void RenderOutroAnimation(SDL_Renderer* renderer, SDL_Texture* spriteSheet, int frameWidth, int frameHeight, int NUM_INTRO_FRAMES, int numRows, int currentFrame, int x, int y, int sheetWidth, int sheetHeight) {

    // Calculate the source rectangle for the current frame
    int row = currentFrame / NUM_OUTRO_FRAMES;
    int col = currentFrame % NUM_OUTRO_FRAMES;
    SDL_Rect srcRect;
    srcRect.x = col * frameWidth;
    srcRect.y = row * frameHeight;
    srcRect.w = frameWidth;
    srcRect.h = frameHeight;

    // Destination rectangle (where to render the frame on the screen)
    SDL_Rect destRect = { x, y, sheetWidth, sheetHeight }; // Adjusted to the entire sprite sheet size

    // Render the current frame
    SDL_RenderCopy(renderer, spriteSheet, &srcRect, &destRect);

}

void RenderOutro() {
    const int repeatCount = 5; // Render the outro 5 times longer

    for (int i = 0; i < NUM_OUTRO_FRAMES * repeatCount; ++i) {

        // Calculate the current frame to render

        int currentFrame = i % NUM_OUTRO_FRAMES;



        // Render the current frame

        RenderOutroAnimation(g_renderer, g_outro, 960, 540, NUM_OUTRO_FRAMES, 1, currentFrame, 0, 0, 960, 540);

        SDL_Delay(80);

        SDL_RenderPresent(g_renderer);

    }

}







void UpdateGuideFrame() {

    static Uint32 lastFrameTime = SDL_GetTicks();

    Uint32 currentTime = SDL_GetTicks();

    Uint32 elapsedTime = currentTime - lastFrameTime;



    if (elapsedTime >= (1000 / GUIDE_FRAME_RATE)) {

        // Update the current frame

        currentGuideFrame++;

        lastFrameTime = currentTime;

    }

}



void RenderGuideAnimation() {

    static int currentGuideFrame = 0; // Static variable to retain its value across function calls

    // Increment currentMenuFrame for next frame
    currentGuideFrame = (currentGuideFrame + 1) % NUM_GUIDE_FRAMES;

    // Clear the renderer
    SDL_RenderClear(g_renderer);

    // Calculate frame width and height
    int frameWidth = 6720 / NUM_GUIDE_FRAMES;
    int frameHeight = 540;
    int row = 0;
    int col = currentGuideFrame;

    SDL_Rect srcRect;
    srcRect.x = col * frameWidth;
    srcRect.y = row * frameHeight;
    srcRect.w = frameWidth;
    srcRect.h = frameHeight;

    // Destination rectangle (where to render the frame on the screen)
    SDL_Rect destRect = { 0, 0, frameWidth, frameHeight }; // Adjusted to the desired size on the screen

    // Render the current frame of the snake animation
    SDL_RenderCopy(g_renderer, g_control, &srcRect, &destRect);
    ApplyTexture1(g_returnButton, 880, 480);

    // Update the screen
    SDL_RenderPresent(g_renderer);
}

void RenderSnakeMenu() {

    int currentMenuFrame = 0; // Initialize current frame

    while (g_gameState == GameState::MENU) {
        RenderMenuAnimation();
        SDL_Delay(100);
    }
}

void RenderSkinScreen() {
    ApplyTexture1(g_skinBackground, 0, 0);
    ApplyTexture1(g_colorSkin, 173, 473);
    ApplyTexture1(g_returnButton, 880, 480);
    RenderColorAnimation();
    RenderSkinSpeedScreen();
    SDL_RenderPresent(g_renderer);
}

void HandleSkinButtonInput() {
    // Open the skin selection screen when the skin button is clicked
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect skinButtonRect = { SKIN_BUTTON_X * zoom_scale, SKIN_BUTTON_Y * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };
    if (IsPointInRect(mouseX, mouseY, skinButtonRect)) {
        g_gameState = GameState::SKIN;
    }
}

void HandleMenuInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            int buttonWidth = 200 * zoom_scale, buttonHeight = 50 * zoom_scale;
            // Define the regions for the buttons based on the menu background image
            SDL_Rect startButtonRect = { 400 * zoom_scale, 150 * zoom_scale, buttonWidth, buttonHeight };
            SDL_Rect loadButtonRect = { 400 * zoom_scale, 230 * zoom_scale, buttonWidth, buttonHeight };
            SDL_Rect settingsButtonRect = { 400 * zoom_scale, 315 * zoom_scale, buttonWidth, buttonHeight };
            SDL_Rect aboutButtonRect = { 400 * zoom_scale, 390 * zoom_scale, buttonWidth, buttonHeight };
            SDL_Rect quitButtonRect = { 400 * zoom_scale, 460 * zoom_scale, buttonWidth, buttonHeight };

            // Define the coordinates and dimensions of other buttons here

            // Check if the mouse click is within any of the button regions
            if (IsPointInRect(mouseX, mouseY, startButtonRect)) {
                g_gameState = GameState::MODE;
            }
            else if (IsPointInRect(mouseX, mouseY, loadButtonRect)) {
                g_gameState = GameState::LOAD;
            }
            else if (IsPointInRect(mouseX, mouseY, settingsButtonRect)) {
                g_gameState = GameState::SETTINGS;
            }
            else if (IsPointInRect(mouseX, mouseY, aboutButtonRect)) {
                g_gameState = GameState::ABOUT;
            }
            else if (IsPointInRect(mouseX, mouseY, quitButtonRect)) {
                g_gameState = GameState::OUTRO;
            }
        }
    }
}

void HandleLeadButtonInput() {
    // Open the skin selection screen when the skin button is clicked
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect skinButtonRect = { LEADER_BUTTON_X * zoom_scale, LEADER_BUTTON_Y * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };
    if (IsPointInRect(mouseX, mouseY, skinButtonRect)) {
        g_gameState = GameState::LEADERBOARD;
    }
}

void HandleGuideButtonInput() {

    // Open the skin selection screen when the skin button is clicked
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Rect guideButtonRect = { GUIDE_BUTTON_X * zoom_scale, GUIDE_BUTTON_Y * zoom_scale, 100 * zoom_scale, 100 * zoom_scale };
    if (IsPointInRect(mouseX, mouseY, guideButtonRect)) {
        g_gameState = GameState::GUIDE;
    }
}




void HandleSettingsInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleReturnButtonInput();
            if (soundOn1) {
                HandleSoundOnButtonInput1();
			}
            else {
				HandleSoundOffButtonInput1();
            }

            if (soundOn2) {
                HandleSoundOnButtonInput2();
            }
            else {
                HandleSoundOffButtonInput2();
            }

            if (soundOn3) {
				HandleSoundOnButtonInput3();
			}
            else {
				HandleSoundOffButtonInput3();
			}

            HandleSkinButtonInput();
            HandleLeadButtonInput();

            HandleGuideButtonInput();
        }
    }
}

void HandleGuideInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleReturnButtonSkinInput();
        }
    }
}


void HandleAboutInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleReturnButtonInput();
        }
    }
}

void HandleQuitInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleReturnButtonInput();
        }
    }
}


void HandlePlayingInput() {

    while (SDL_PollEvent(&g_event)) {

        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }

        else if (g_event.type == SDL_KEYDOWN && !lockMovement && !lockDir) {
            switch (g_event.key.keysym.sym) {
            case SDLK_p:
                snakeDirection = PAUSE;
                break;
            case SDLK_w:
                snakeDirection = UP;

                break;
            case SDLK_UP:
                snakeDirection = UP;

                break;
            case SDLK_a:
                snakeDirection = LEFT;

                break;
            case SDLK_LEFT:
                snakeDirection = LEFT;

                break;
            case SDLK_s:
                snakeDirection = DOWN;

                break;
            case SDLK_DOWN:
                snakeDirection = DOWN;

                break;
            case SDLK_d:
                snakeDirection = RIGHT;

                break;
            case SDLK_RIGHT:
                snakeDirection = RIGHT;

                break;
            case SDLK_o:
                g_gameState = GameState::ASK;
                break;
            }
        }
    }
}

void UpdateStats() {
    snakeLength++; // Or update according to your game logic
    score += 10; // Or update according to your game logic
}

void UpdateStatsBar() {
    if (g_statsBars != nullptr) {
        SDL_DestroyTexture(g_statsBars);
        g_statsBars = nullptr;
    }
    std::string filePath;
    if (!specialMode && currentLevel < 6) {
        // Increment foodCount to move to the next stats bar texture
        foodCount = (foodCount + 1) % 6; // Ensure foodCount stays within range [0, 5]
        filePath = "Foodbar." + std::to_string(foodCount) + ".png";
    }
    else {
        foodCount++;
        filePath = "Foodbar." + std::to_string(5) + ".png";
    }
    g_statsBars = LoadTexture(filePath);
    if (g_statsBars == nullptr) {
        // Handle the case when the texture failed to load
        // For example, you might want to load a default texture
        g_statsBars = LoadTexture("Foodbar.0.png");
    }
}

void UpdateSpeedSkinBar() {
    if (g_speedBars != nullptr) {
        SDL_DestroyTexture(g_speedBars);
        g_speedBars = nullptr;
    }

    std::string filePath = "speed" + std::to_string(speed) + "Skin.png";
    g_speedBars = LoadTexture(filePath);
    if (g_speedBars == nullptr) {
        g_speedBars = LoadTexture("speed1Skin.png");
    }
}

void HandleSkinInput() {
    while (SDL_PollEvent(&g_event)) {

        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }

        else if (g_event.type == SDL_KEYDOWN) {
            switch (g_event.key.keysym.sym) {
            case SDLK_UP:
                speed++;
                if (speed > 3) {
                    speed = maxSpeed;
                }
                UpdateSpeedSkinBar();
                COLOR_FRAME_RATE += FRAME_RATE_INCREMENT;
                if (COLOR_FRAME_RATE > MAX_COLOR_FRAME_RATE) {
                    COLOR_FRAME_RATE = MAX_COLOR_FRAME_RATE;
                }
                break;
            case SDLK_DOWN:
                speed--;
                if (speed < 1) {
                    speed = minSpeed;
                }
                UpdateSpeedSkinBar();
                COLOR_FRAME_RATE -= FRAME_RATE_INCREMENT;
                if (COLOR_FRAME_RATE < MIN_COLOR_FRAME_RATE) {
                    COLOR_FRAME_RATE = MIN_COLOR_FRAME_RATE;
                }
                break;
            case SDLK_LEFT:
                currentColorIndex--;
                if (currentColorIndex < 0) {
                    currentColorIndex = NUM_COLORS - 1; // Wrap around to the last color
                }
                break;
            case SDLK_RIGHT:
                currentColorIndex++;
                if (currentColorIndex >= NUM_COLORS) {
                    currentColorIndex = 0;  // Wrap around to the first color
                }
                break;
            }
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleReturnButtonSkinInput();
        }
    }
}

void RenderText(const std::string& text, int x, int y) {
    SDL_Color color = { 0, 0, 0, 255 }; // Black color
    SDL_Surface* surface = TTF_RenderText_Solid(g_font, text.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_FreeSurface(surface);
    SDL_RenderCopy(g_renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}


void RenderLevelStats() {
    
    if (!(!specialMode && currentLevel > 4)) {
        std::string levelText = "Level: " + std::to_string(currentLevel);
        RenderText(levelText, 740, 10);
    }
    std::string foodText = "Food: " + std::to_string(foodCount);
    std::string lengthText = "Length: " + std::to_string(snakeLength);
    std::string speedText = "Speed: " + std::to_string(PIXEL_PER_LOOP);
    std::string scoreText = "Score: " + std::to_string(score);

    RenderText(foodText, 720, 70);
    RenderText(lengthText, 720, 120);
    RenderText(speedText, 720, 170);
    RenderText(scoreText, 720, 220);
   
    if (foodCount >= 0 && foodCount <= 5 && g_statsBars != nullptr) {
        SDL_QueryTexture(g_statsBars, NULL, NULL, &foodBarWidth, &foodBarHeight);
        ApplyTexture2(g_statsBars, 800, 250, foodBarWidth * 2,foodBarHeight * 2);
    }
}

void RenderMenu() {
    // Play background music when rendering the menu
    ApplyTexture1(g_menuBackground, 0, 0);
    PlayMenuBackgroundMusic();
    SDL_RenderPresent(g_renderer);
}


// Function to render the leaderboard

void RenderLoadText(const std::vector<Player>& players) {

    int lineHeight = 40; // Height of each line
    int yPos = 172; // Initial y position for rendering

    // Render player entries for the first 5 players
    for (size_t i = 0; i < min(players.size(), size_t(8)); ++i) {
        std::string playerInfo = players[i].name + "     " + std::to_string(players[i].score) + "  " + players[i].dateAndTime;
        RenderText(playerInfo, 245, yPos);
        yPos += lineHeight; // Move down for next player entry
    }
}

// Define a global variable to store the y-position of the load button
int loadButtonY = 180;

void RenderLoadScreen() {
    ApplyTexture1(g_loadGame, 0, 0);

    RenderLoadText(players);

    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);

    // Apply the load button texture at the updated y-position
    ApplyTexture1(g_loadButton, 50, loadButtonY);

    SDL_RenderPresent(g_renderer);
}

int playerSelectCount = 1;

void HandleLoadInput() {


    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_KEYDOWN) {
            switch (g_event.key.keysym.sym) {
            case SDLK_UP:
                loadButtonY -= 40;
                playerSelectCount--;

                break;

            case SDLK_DOWN:
                loadButtonY += 40;
                playerSelectCount++;

                break;

            case SDLK_RETURN:
                currentLevel = players[playerSelectCount - 1].score / (10 * 5) + 1;
                g_gameState = GameState::PLAYING;

                break;

            }
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleReturnButtonInput();
        }
    }
}

void RenderSettingsScreen() {

    std::string soundOn = "SOUND ON";
    std::string soundOff = "SOUND OFF";
    std::string skinSnake = "CHOOSE YOUR SNAKE";
    std::string leaderboard = "LEADERBOARD";

    ApplyTexture1(g_settings, 0, 0);
    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);
   
    if (soundOn1) {
        ApplyTexture2(g_soundOnButton1, SOUND_ON_BUTTON_X + 380, SOUND_ON_BUTTON_Y + 75, 100 * zoom_scale, 100 * zoom_scale);
    }
    else ApplyTexture2(g_soundOffButton1, SOUND_ON_BUTTON_X + 380, SOUND_ON_BUTTON_Y + 75, 100 * zoom_scale, 100 * zoom_scale);
    if (soundOn2) {
        ApplyTexture2(g_soundOnButton2, SOUND_ON_BUTTON_X + 380, SOUND_ON_BUTTON_Y + 160, 100 * zoom_scale, 100 * zoom_scale);
    }
    else ApplyTexture2(g_soundOffButton2, SOUND_ON_BUTTON_X + 380, SOUND_ON_BUTTON_Y + 160, 100 * zoom_scale, 100 * zoom_scale);
    if (soundOn3) {
        ApplyTexture2(g_soundOnButton3, SOUND_ON_BUTTON_X + 380, SOUND_ON_BUTTON_Y + 245, 100 * zoom_scale, 100 * zoom_scale);
    }
    else ApplyTexture2(g_soundOffButton3, SOUND_ON_BUTTON_X + 380, SOUND_ON_BUTTON_Y + 245, 100 * zoom_scale, 100 * zoom_scale);

    //ApplyTexture1(g_soundOffButton, SOUND_OFF_BUTTON_X, SOUND_OFF_BUTTON_Y);
    ApplyTexture2(g_MusicOption, MUSIC_OPTION_X - 100, MUSIC_OPTION_Y + 75, 500, 300);



    ApplyTexture1(g_skinButton, SKIN_BUTTON_X, SKIN_BUTTON_Y);
    ApplyTexture1(g_leaderboardButton, LEADER_BUTTON_X, LEADER_BUTTON_Y);
    ApplyTexture1(g_guideButton, GUIDE_BUTTON_X, GUIDE_BUTTON_Y);

    
    RenderText(skinSnake, 575, 273);
    RenderText(leaderboard, 575, 450);

    SDL_RenderPresent(g_renderer);
}

void RenderAboutScreen() {
    ApplyTexture1(g_aboutUs, 0, 0);
    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);
    SDL_RenderPresent(g_renderer);
}

void RenderQuitScreen() {
    ApplyTexture1(g_quit, 0, 0);
    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);
    SDL_RenderPresent(g_renderer);
}

void HandleModeInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            int buttonWidth = 200 * zoom_scale, buttonHeight = 50 * zoom_scale;
            // Define the regions for the buttons based on the menu background image
            SDL_Rect levelButtonRect = { 194, 313, buttonWidth, buttonHeight };
            SDL_Rect specialButtonRect = { 561, 312, buttonWidth, buttonHeight };

            // Define the coordinates and dimensions of other buttons here

            // Check if the mouse click is within any of the button regions
            if (IsPointInRect(mouseX, mouseY, levelButtonRect)) {
                g_gameState = GameState::PLAYING;
            }
            else if (IsPointInRect(mouseX, mouseY, specialButtonRect)) {
                g_gameState = GameState::SPECIAL;
            }
            else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
                HandleReturnButtonInput();
            }
        }
    }
}

void RenderModeScreen() {

    ApplyTexture2(g_mode, 0, 0, 2880, 540);
    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);
    SDL_RenderPresent(g_renderer);
}

void RenderPauseMenu() {

    // Clear the renderer
    //SDL_RenderClear(g_renderer);
    // Render the pause menu texture onto the screen
    ApplyTexture2(g_pauseMenu,705, 250, 194, 225);

    // Present the renderer
    SDL_RenderPresent(g_renderer);
}

void HandlePauseMenuInput() {
    if (snakeDirection == PAUSE) {
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
            else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                std::cout << "Mouse: " << mouseX << ", " << mouseY << std::endl;

                SDL_Rect SaveButtonRect = { 728 * zoom_scale, 302 * zoom_scale, 150 * zoom_scale, 50 * zoom_scale };;
                SDL_Rect ContinueButtonRect = { 728 * zoom_scale, 364 * zoom_scale, 150 * zoom_scale, 50 * zoom_scale };
                SDL_Rect QuitGameButtonRect = { 728 * zoom_scale, 420 * zoom_scale, 150 * zoom_scale, 50 * zoom_scale };

                if (IsPointInRect(mouseX, mouseY, SaveButtonRect)) {
                    g_gameState = GameState::SAVE;
				}
                else if (IsPointInRect(mouseX, mouseY, ContinueButtonRect)) {
                    HandleContinueButtonInput();
                }
                else if (IsPointInRect(mouseX, mouseY, QuitGameButtonRect)) {
                    g_gameState = GameState::OUTRO;
                }
            }
        }
    }
}

void HandleContinueButtonInput() {

    snakeDirection = lastDirection;

}


void setupAndQuery_Level() {
    if (setupForLevel) {
        SDL_QueryTexture(g_bkground, NULL, NULL, &bkWidth, &bkHeight);
        SDL_QueryTexture(g_food, NULL, NULL, &foodWidth_png, &foodHeight_png);
        SDL_QueryTexture(g_snake, NULL, NULL, &snakeWidth_png, &snakeHeight_png);
        SDL_QueryTexture(g_pauseMenu, NULL, NULL, &pauseMenuWidth, &pauseMenuHeight);

        foodWidth = 16, foodHeight = 16;
        snakeWidth = snakeWidth_png * snakeScale, snakeHeight = snakeHeight_png * snakeScale;


        // Play background music when rendering the menu
        //PlayBackgroundMusic();

        // Initialize level
        Level(currentLevel);

        g_statsBars = LoadTexture("Foodbar.0.png");

        g_monster1 = LoadTexture("monster1.gif");
        g_monster2 = LoadTexture("monster2.gif");

        g_ouroboros = LoadTexture("Ouroboros.png");

        setupForLevel = false;
    }
}

void setupAndQuery_Special() {
    if (setupForSpecial) {
        specialMode = true;
        SDL_QueryTexture(g_bkground, NULL, NULL, &bkWidth, &bkHeight);
        SDL_QueryTexture(g_food, NULL, NULL, &foodWidth_png, &foodHeight_png);
        SDL_QueryTexture(g_snake, NULL, NULL, &snakeWidth_png, &snakeHeight_png);
        SDL_QueryTexture(g_pauseMenu, NULL, NULL, &pauseMenuWidth, &pauseMenuHeight);

        g_iceTile = LoadTexture("iceTile.png");

        foodWidth = 16, foodHeight = 16;
        snakeWidth = snakeWidth_png * snakeScale, snakeHeight = snakeHeight_png * snakeScale;


        // Initialize level
        Level_Special(currentLevel);

        g_statsBars = LoadTexture("Foodbar.0.png");

        setupForSpecial = false;
    }
}

void RenderPlaying_Level() {

    ApplyTexture2(g_bkground, 0, 0, bkWidth, bkHeight);

    RenderLevelStats();

    renderOuroboros();

    mapTile(1);
    
    RenderToggleObstacles_Draw_Level2();

    if (show_food) {
        //RenderHitbox(g_renderer, foodX - foodWidth / 2, foodY - foodHeight / 2, foodWidth, foodHeight);
        ApplyTexture2(g_food, foodX - foodWidth / 2, foodY - foodHeight / 2, foodWidth, foodHeight);
    }
    RenderPlayingSkin();
    //RenderHitbox(g_renderer, snakeX - snakeWidth / 2, snakeY - snakeHeight / 2, snakeWidth, snakeHeight);
    ApplyTexture2(g_snake, snakeX - snakeWidth / 2, snakeY - snakeHeight / 2, snakeWidth, snakeHeight);

    DrawTail();

    renderMonster();

    RenderToggleObstacles_Fill_Level2();

    RenderMovingObstacles(g_renderer);

    RenderObstacles(g_renderer);
    RenderPortals(g_renderer);

    RenderSubPortal(g_renderer);
    
    if (!gate_open_step[0] && !gate_open_step[1] && goOutGate_progress) fake_portal_gate();

    DreamLogic();
    RenderDreamBlock();

    if (snakeDirection == PAUSE) {

        RenderPauseMenu();
    }

    SDL_RenderPresent(g_renderer);
}

void RenderPlaying_Special() {
    ApplyTexture2(g_bkground, 0, 0, bkWidth, bkHeight);

    RenderLevelStats();

    if (currentLevel != 2) mapTile(2);
    else mapTile(3);


    RenderIceTile(g_renderer);

    iceTileLogic();
    DreamLogic();

    RenderFixedFood();

    RenderIcePortal();



    RenderPlayingSkin();
    //RenderHitbox(g_renderer, snakeX - snakeWidth / 2, snakeY - snakeHeight / 2, snakeWidth, snakeHeight);
    ApplyTexture2(g_snake, snakeX - snakeWidth / 2, snakeY - snakeHeight / 2, snakeWidth, snakeHeight);

    DrawTail();

    RenderObstacles(g_renderer);
    RenderPortals(g_renderer);

    if (!gate_open_step[0] && !gate_open_step[1] && goOutGate_progress) fake_portal_gate();

    RenderDreamBlock();

    if (snakeDirection == PAUSE) {

        RenderPauseMenu();
    }

    SDL_RenderPresent(g_renderer);
}

/*
void RenderDreamBlock() {
    ApplyTexture1(g_dreamBlock, 0, 30);
    ApplyTexture1(g_dreamBlock1, 500, 500);
}
*/


void HandleGameOver() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            int buttonWidth = 50 * zoom_scale, buttonHeight = 50 * zoom_scale;
            // Define the regions for the buttons based on the menu background image
            SDL_Rect yesButtonRect = { 362 * zoom_scale, 466 * zoom_scale, buttonWidth, buttonHeight };
            SDL_Rect noButtonRect = { 562 * zoom_scale, 464 * zoom_scale, buttonWidth, buttonHeight };

            if (IsPointInRect(mouseX, mouseY, yesButtonRect)) {
                g_gameState = GameState::SAVE;
            }
            else if (IsPointInRect(mouseX, mouseY, noButtonRect)) {
                g_gameState = GameState::MENU;
            }
        }
    }
}

void RenderGameOver() {
    ApplyTexture1(g_gameOver, 250, 30);
    SDL_RenderPresent(g_renderer);
}

void HandleTimer() {
    StopBackgroundMusic();
    PlayCountMusic();
    UpdateTimer();
    RenderCount();
    SDL_Delay(1000);
}

/*
Player player; // Declare an instance of the Player struct

void RenderSave() {
    ApplyTexture1(g_snakeEnter, 250, 30); // Assuming ApplyTexture1 is your function to render the PNG texture

    // Render the player's name onto the PNG texture
   // Check if the player's name is valid
    SDL_Color textColor = { 0, 0, 255 };

    // Render the player's name onto the PNG texture
    // Define maximum width for text wrapping
    int maxWidth = 200; // Adjust as needed

    // Render the player's name onto the text surface with wrapping
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(g_font, player.name.c_str(), textColor, maxWidth);
    if (!textSurface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        // Handle the error appropriately (return or other actions)
    }


    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface); // Free the surface before returning
        // Handle the error appropriately (return or other actions)
    }

    SDL_Rect textNameRect = { 336, 375, 320, 30 };
    SDL_RenderCopy(g_renderer, textTexture, nullptr, &textNameRect);

    // Free the surface and texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);


    // Present the renderer
    SDL_RenderPresent(g_renderer);
}



// Function to save the player's name, score, and current date/time to a text file
void SavePlayerInfo(const std::string& playerName, int score) {
    // Get the current date and time
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string dateTimeString = std::ctime(&currentTime);

    // Create a new player object with the given name, score, and current date/time
    Player newPlayer;
    newPlayer.name = playerName;
    newPlayer.score = score;
    newPlayer.dateAndTime = dateTimeString;

    // Add the new player to the array of players
    players.push_back(newPlayer);

    // Write player information to a text file
    std::ofstream outputFile("player_info.txt", std::ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile <<  playerName << " " << score << " " << dateTimeString;
        outputFile.close();
        std::cout << "Player information saved to file." << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }

    // Print confirmation message
    std::cout << "Player name saved: " << playerName << ", Score: " << score << ", Date and Time: " << dateTimeString;
}

// Function to handle input events and save player information
void HandleSaveInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_TEXTINPUT) {
            // Append the input character to the player's name string
            player.name += g_event.text.text;
            std::cout << "Player name: " << player.name << std::endl; // Just for demonstration
        }
        else if (g_event.type == SDL_KEYDOWN) {
            if (g_event.key.keysym.sym == SDLK_RETURN || g_event.key.keysym.sym == SDLK_RETURN2 || g_event.key.keysym.sym == SDLK_KP_ENTER) {
                SavePlayerInfo(player.name, score);
                g_gameState = GameState::QUIT;
            }
        }
    }
}
*/

/*
Player player; // Declare an instance of the Player struct

void RenderSave() {
    ApplyTexture1(g_snakeEnter, 250, 30); // Assuming ApplyTexture1 is your function to render the PNG texture

    // Render the player's name onto the PNG texture
   // Check if the player's name is valid
    SDL_Color textColor = { 0, 0, 255 };

    // Render the player's name onto the PNG texture
    // Define maximum width for text wrapping
    int maxWidth = 200; // Adjust as needed

    // Render the player's name onto the text surface with wrapping
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(g_font, player.name.c_str(), textColor, maxWidth);
    if (!textSurface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        // Handle the error appropriately (return or other actions)
    }


    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface); // Free the surface before returning
        // Handle the error appropriately (return or other actions)
    }

    SDL_Rect textNameRect = { 336, 375, 320, 30 };
    SDL_RenderCopy(g_renderer, textTexture, nullptr, &textNameRect);

    // Free the surface and texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);


    // Present the renderer
    SDL_RenderPresent(g_renderer);
}



// Function to save the player's name, score, and current date/time to a text file
void SavePlayerInfo(const std::string& playerName, int score) {
    // Get the current date and time
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string dateTimeString = std::ctime(&currentTime);

    // Create a new player object with the given name, score, and current date/time
    Player newPlayer;
    newPlayer.name = playerName;
    newPlayer.score = score;
    newPlayer.dateAndTime = dateTimeString;

    // Add the new player to the array of players
    players.push_back(newPlayer);

    // Write player information to a text file
    std::ofstream outputFile("player_info.txt", std::ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile <<  playerName << " " << score << " " << dateTimeString;
        outputFile.close();
        std::cout << "Player information saved to file." << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }

    // Print confirmation message
    std::cout << "Player name saved: " << playerName << ", Score: " << score << ", Date and Time: " << dateTimeString;
}

// Function to handle input events and save player information
void HandleSaveInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_TEXTINPUT) {
            // Append the input character to the player's name string
            player.name += g_event.text.text;
            std::cout << "Player name: " << player.name << std::endl; // Just for demonstration
        }
        else if (g_event.type == SDL_KEYDOWN) {
            if (g_event.key.keysym.sym == SDLK_RETURN || g_event.key.keysym.sym == SDLK_RETURN2 || g_event.key.keysym.sym == SDLK_KP_ENTER) {
                SavePlayerInfo(player.name, score);
                g_gameState = GameState::QUIT;
            }
        }
    }
}

*/

void setZoom(float zoom) {
    SDL_RenderSetScale(g_renderer, zoom, zoom);
}

Player player; // Declare an instance of the Player struct

void RenderSave() {
    ApplyTexture1(g_snakeEnter, 250, 30);

    SDL_Color textColor = { 0, 0, 255 };
    int maxWidth = 200; // Adjust as needed

    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(g_font, player.name.c_str(), textColor, maxWidth);

    if (!textSurface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        // Handle the error appropriately (return or other actions)
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface); // Free the surface before returning
        // Handle the error appropriately (return or other actions)
    }

    SDL_Rect textNameRect = { 336, 375, 320, 30 };
    SDL_RenderCopy(g_renderer, textTexture, nullptr, &textNameRect);

    // Free the surface and texture
    SDL_FreeSurface(textSurface);

    SDL_DestroyTexture(textTexture);

    // Present the renderer
    SDL_RenderPresent(g_renderer);
}

// Function to save the player's name, score, and current date/time to a text file
void SavePlayerInfo(const std::string& playerName, int score) {

    // Get the current date and time

    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string dateTimeString = std::ctime(&currentTime);



    // Create a new player object with the given name, score, and current date/time

    Player newPlayer;

    newPlayer.name = playerName;

    newPlayer.score = score;

    newPlayer.dateAndTime = dateTimeString;



    // Add the new player to the array of players

    players.push_back(newPlayer);



    // Write player information to a text file

    std::ofstream outputFile("player_info.txt", std::ios::app); // Open the file in append mode

    if (outputFile.is_open()) {

        outputFile << playerName << " " << score << " " << dateTimeString;

        outputFile.close();

        std::cout << "Player information saved to file." << std::endl;

    }

    else {

        std::cerr << "Error: Unable to open file for writing." << std::endl;

    }



    // Print confirmation message

    std::cout << "Player name saved: " << playerName << ", Score: " << score << ", Date and Time: " << dateTimeString;

}

// Function to handle input events and save player information
void HandleSaveInput() {

    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }

        else if (g_event.type == SDL_TEXTINPUT) {
            // Append the input character to the player's name string
            player.name += g_event.text.text;
            std::cout << "Player name: " << player.name << std::endl; // Just for demonstration
        }
        else if (g_event.type == SDL_KEYDOWN) {
            if (g_event.key.keysym.sym == SDLK_RETURN || g_event.key.keysym.sym == SDLK_RETURN2 || g_event.key.keysym.sym == SDLK_KP_ENTER) {
                SavePlayerInfo(player.name, score);
                g_gameState = GameState::OUTRO;
            }
        }
    }
}

void HandleLeadInput() {

    while (SDL_PollEvent(&g_event)) {

        if (g_event.type == SDL_QUIT) {

            SDL_Quit();

            exit(0);

        }

        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {

            int mouseX, mouseY;

            SDL_GetMouseState(&mouseX, &mouseY);

            HandleReturnButtonInput();

        }

    }



}

// Function to render the leaderboard
void RenderLeaderboard(const std::vector<Player>& players) {

    int lineHeight = 50; // Height of each line

    int yPos = 252; // Initial y position for rendering

    highScore();

    // Render player entries for the first 5 players

    for (size_t i = 0; i < min(players.size(), size_t(5)); ++i) {

        std::string playerInfo = players[i].name + "     " + std::to_string(players[i].score) + "  " + players[i].dateAndTime;

        RenderText(playerInfo, 245, yPos);

        yPos += lineHeight; // Move down for next player entry

    }

}

void RenderLeadScreen() {

    int x, y;

    SDL_QueryTexture(g_leaderboard, NULL, NULL, &x, &y);

    ApplyTexture2(g_leaderboard, 0, 0, 960, 540);

    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);

    RenderLeaderboard(players);

    SDL_RenderPresent(g_renderer);

}
