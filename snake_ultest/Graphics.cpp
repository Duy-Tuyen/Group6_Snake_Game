#include "Graphics.h"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_bkground = nullptr;
SDL_Texture* g_snake = nullptr;
SDL_Texture* g_food = nullptr;
SDL_Texture* g_statsBars = nullptr; // Array to hold textures for six stats bars
SDL_Texture* g_menuBackground = nullptr;
SDL_Texture* g_aboutUs = nullptr;
SDL_Texture* g_loadGame = nullptr;
SDL_Texture* g_settings = nullptr;
SDL_Texture* g_quit = nullptr;
SDL_Texture* g_returnButton = nullptr;
SDL_Texture* g_soundOnButton = nullptr;
SDL_Texture* g_soundOffButton = nullptr;

Mix_Music* g_backgroundMusic = nullptr;
Mix_Music* g_scoreMusic = nullptr;
Mix_Music* g_hurtMusic = nullptr;

SDL_Event g_event;
GameState g_gameState = GameState::MENU;

const int RETURN_BUTTON_X = 450;
const int RETURN_BUTTON_Y = 490;
const int SOUND_ON_BUTTON_X = 100;
const int SOUND_ON_BUTTON_Y = 100;
const int SOUND_OFF_BUTTON_X = 100;
const int SOUND_OFF_BUTTON_Y = 300;

// Level statistics
int level = 1;
int foodCount = 0;
int snakeLength = 1;
int score = 0;
int foodBarWidth, foodBarHeight;
// Font for rendering text
TTF_Font* g_font = nullptr;

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
    // Load background music
    g_scoreMusic = Mix_LoadMUS("score.wav");
    if (g_backgroundMusic == nullptr) {
        std::cerr << "Failed to load score music: " << Mix_GetError() << std::endl;
        return false;
    }// Load background music
    g_hurtMusic = Mix_LoadMUS("hurt.wav");
    if (g_backgroundMusic == nullptr) {
        std::cerr << "Failed to load hurt music: " << Mix_GetError() << std::endl;
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

    // Load textures
    g_menuBackground = LoadTexture("menuBackground.png");
    if (g_menuBackground == nullptr) {
        return false;
    }

    g_loadGame = LoadTexture("loadGame.png");
    if (g_loadGame == nullptr) {
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

    g_bkground = LoadTexture("playingBackground.png");
    if (g_bkground == nullptr) {
        return false;
    }

    g_snake = LoadTexture("2.png");
    if (g_snake == nullptr) {
        return false;
    }


    g_food = LoadTexture("Food.png");
    if (g_food == nullptr) {
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
    Mix_FreeMusic(g_scoreMusic);
    Mix_FreeMusic(g_hurtMusic);
    // Quit SDL_mixer
    Mix_CloseAudio();

    SDL_DestroyTexture(g_menuBackground);
    SDL_DestroyTexture(g_aboutUs);
    SDL_DestroyTexture(g_loadGame);
    SDL_DestroyTexture(g_settings);
    SDL_DestroyTexture(g_quit);
    SDL_DestroyTexture(g_bkground);
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
    Mix_HaltMusic();
}

void PlayMenuBackgroundMusic() {
    if (Mix_PlayingMusic() == 0) {
        // If no music is playing, start playing the background music
        Mix_PlayMusic(g_backgroundMusic, -1);
    }
}

void PlayScoreMusic() {
    if (Mix_PlayingMusic() == 0) {
        // If no music is playing, start playing the background music
        Mix_PlayMusic(g_scoreMusic, 1);
    }
}

void PlayHurtMusic() {
    if (Mix_PlayingMusic() == 0) {
        // If no music is playing, start playing the background music
        Mix_PlayMusic(g_hurtMusic, 1);
    }
}

void HandleReturnButtonInput() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect returnButtonRect = { RETURN_BUTTON_X, RETURN_BUTTON_Y, 20, 20 };
    if (IsPointInRect(mouseX, mouseY, returnButtonRect)) {
        g_gameState = GameState::MENU;
    }
}
void HandleSoundOnButtonInput() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOnButtonRect = { SOUND_ON_BUTTON_X, SOUND_ON_BUTTON_Y, 100, 100 };
    if (IsPointInRect(mouseX, mouseY, soundOnButtonRect)) {
        PlayBackgroundMusic();
    }
}
void HandleSoundOffButtonInput() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect soundOffButtonRect = { SOUND_OFF_BUTTON_X, SOUND_OFF_BUTTON_Y, 100, 300 };
    if (IsPointInRect(mouseX, mouseY, soundOffButtonRect)) {
        StopBackgroundMusic();
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

            // Define the regions for the buttons based on the menu background image
            SDL_Rect startButtonRect = { 400, 150, 50, 30 };
            SDL_Rect loadButtonRect = { 400, 230, 50, 30 };
            SDL_Rect settingsButtonRect = { 400, 315, 50, 30 };
            SDL_Rect aboutButtonRect = { 400, 390, 50, 30 };
            SDL_Rect quitButtonRect = { 400, 460, 50, 30 };

            // Define the coordinates and dimensions of other buttons here

            // Check if the mouse click is within any of the button regions
            if (IsPointInRect(mouseX, mouseY, startButtonRect)) {
                g_gameState = GameState::PLAYING;
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
                g_gameState = GameState::QUIT;
            }
        }
    }
}

void HandleLoadInput() {
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
void HandleSettingsInput() {
    while (SDL_PollEvent(&g_event)) {
        if (g_event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleReturnButtonInput();
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleSoundOnButtonInput();
        }
        else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
            HandleSoundOffButtonInput();
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

        else if (g_event.type == SDL_KEYDOWN) {
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
    // Increment foodCount to move to the next stats bar texture
    foodCount = (foodCount + 1) % 6; // Ensure foodCount stays within range [0, 5]
    std::string filePath = "Foodbar." + std::to_string(foodCount) + ".png";
    g_statsBars = LoadTexture(filePath);
    if (g_statsBars == nullptr) {
        // Handle the case when the texture failed to load
        // For example, you might want to load a default texture
        g_statsBars = LoadTexture("Foodbar.0.png");
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
    std::string levelText = "Level: " + std::to_string(level);
    std::string foodText = "Food: " + std::to_string(foodCount);
    std::string lengthText = "Length: " + std::to_string(snakeLength);
    std::string scoreText = "Score: " + std::to_string(score);

    RenderText(levelText, 740, 10);
    RenderText(foodText, 720, 70);
    RenderText(lengthText, 720, 120);
    RenderText(scoreText, 720, 170);
    int foodBarWidth, foodBarHeight;
    SDL_QueryTexture(g_statsBars, NULL, NULL, &foodBarWidth, &foodBarHeight);
    if (foodCount >= 0 && foodCount <= 5 && g_statsBars != nullptr) {
        ApplyTexture2(g_statsBars, 800, 250,foodBarWidth * 2,foodBarHeight*2);
    }
}

void RenderMenu() {
    // Play background music when rendering the menu
    PlayMenuBackgroundMusic();
    ApplyTexture1(g_menuBackground, 0, 0);
    SDL_RenderPresent(g_renderer);
}

void RenderLoadScreen() {
    ApplyTexture1(g_loadGame, 0, 0);
    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);
    SDL_RenderPresent(g_renderer);
}

void RenderSettingsScreen() {
    ApplyTexture1(g_settings, 0, 0);
    ApplyTexture1(g_returnButton, RETURN_BUTTON_X, RETURN_BUTTON_Y);
    ApplyTexture1(g_soundOnButton, SOUND_ON_BUTTON_X, SOUND_ON_BUTTON_Y);
    ApplyTexture1(g_soundOffButton, SOUND_OFF_BUTTON_X, SOUND_OFF_BUTTON_Y);
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

void RenderPlaying() {
    ApplyTexture2(g_bkground, 0, 0, bkWidth, bkHeight);
    SDL_QueryTexture(g_bkground, NULL, NULL, &bkWidth, &bkHeight);
    if (show_food) {
        ApplyTexture2(g_food, foodX, foodY, foodWidth * 2, foodHeight * 2);
        SDL_QueryTexture(g_food, NULL, NULL, &foodWidth, &foodHeight);
    }
    ApplyTexture2(g_snake, snakeX, snakeY, snakeWidth * 1.5, snakeHeight * 1.5);
    SDL_QueryTexture(g_snake, NULL, NULL, &snakeWidth, &snakeHeight);
    RenderLevelStats();
    SDL_RenderPresent(g_renderer);
}