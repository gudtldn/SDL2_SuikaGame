#include "Core.h"
#include "GameState.h"
#include "SuikaGame/Menu/MainMenu.h"
#include "SuikaGame/Game/Game.h"

// https://lazyfoo.net/tutorials/SDL/index.php

int main(int argc, char* args[])
{
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR(LogGame, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    // SDL_Image 초기화
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        LOG_ERROR(LogGame, "SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
        return -1;
    }

    // SDL_TTF 초기화
    if (TTF_Init() == -1)
    {
        LOG_ERROR(LogGame, "SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError());
        return -1;
    }

    // SDL_Mixer 초기화
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        LOG_ERROR(LogGame, "SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
        return -1;
    }

    // BGM 로드
    Mix_Music* bgm = Mix_LoadMUS("Contents/Sounds/suika_game_bgm.mp3");
    if (bgm == NULL)
    {
        LOG_ERROR(LogGame, "Failed to load bgm! SDL_mixer Error: %s", Mix_GetError());
    }

    // Screen Size 가져오기
    SDL_DisplayMode DM;
    if (SDL_GetCurrentDisplayMode(0, &DM) != 0)
    {
        LOG_ERROR(LogGame, "SDL_GetCurrentDisplayMode failed: %s", SDL_GetError());
        return -1;
    }

    // 화면 초기화
    ScreenConfigBuilder screen_config = GetDefaultScreenConfigBuilder();
    screen_config.screen_width = (int)(DM.w / 1.5);
    screen_config.screen_height = (int)(DM.h / 1.5);
    screen_config.screen_x = DM.w / 2 - screen_config.screen_width / 2;
    screen_config.screen_y = DM.h / 2 - screen_config.screen_height / 2;

    View view;
    if (CreateWindow(&view, "SuikaGame", &screen_config) != CREATE_WINDOW_SUCCESS)
    {
        LOG_ERROR(LogGame, "Failed to initialize!");
        return -1;
    }

    // BGM 재생
    if (Mix_PlayMusic(bgm, -1) == -1)
    {
        LOG_ERROR(LogGame, "Failed to play bgm! SDL_mixer Error: %s", Mix_GetError());
    }

    // 프로그램 루프
    SetCurrentAppState(AppState_MainMenu);
    while (GetCurrentAppState() != AppState_Exit)
    {
        // 프로그램 상태에 따른 처리
        switch (GetCurrentAppState())
        {
        case AppState_MainMenu:
            IntoMainMenu(&view);
            break;
        case AppState_Game:
            IntoGame(&view);
            break;
        }
    }

    // SDL 종료
    IMG_Quit();
    TTF_Quit();
    if (bgm != NULL)
        Mix_FreeMusic(bgm);
    CloseWindow(&view);

    return 0;
}
