#include "Core.h"
#include "GameState.h"
#include "SuikaGame/Menu/MainMenu.h"
#include "SuikaGame/Game/Game.h"

#include <locale.h>

// 오류 핸들러
#define ERROR_HANDLER(condition, message, ...)      \
    if (condition)                                  \
    {                                               \
        LOG_ERROR(LogGame, message, ##__VA_ARGS__); \
        return -1;                                  \
    }

// https://lazyfoo.net/tutorials/SDL/index.php
// https://www.youtube.com/watch?v=BDqJUJ-jOSQ
// https://box2d.org/documentation/hello.html
// https://wikidocs.net/book/6636

int main(int argc, char* args[])
{
    // 로케일 설정
    setlocale(LC_ALL, "ko_KR.UTF-8");

    // SDL 초기화
    ERROR_HANDLER(
        SDL_Init(SDL_INIT_VIDEO) < 0,
        "SDL could not initialize! SDL_Error: %s", SDL_GetError()
    )

    // SDL_Image 초기화
    ERROR_HANDLER(
        (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0,
        "SDL_image could not initialize! SDL_image Error: %s", IMG_GetError()
    )

    // SDL_TTF 초기화
    ERROR_HANDLER(
        TTF_Init() == -1,
        "SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError()
    )

    // SDL_Mixer 초기화
    ERROR_HANDLER(
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0,
        "SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError()
    )

    // BGM 로드
    Mix_Music* bgm = Mix_LoadMUS("Contents/Sounds/suika_game_bgm.mp3");
    if (bgm == NULL)
    {
        LOG_ERROR(LogGame, "Failed to load bgm! SDL_mixer Error: %s", Mix_GetError());
    }

    // Screen Size 가져오기
    SDL_DisplayMode DM;
    ERROR_HANDLER(
        SDL_GetCurrentDisplayMode(0, &DM) != 0,
        "SDL_GetCurrentDisplayMode failed: %s", SDL_GetError()
    )

    // 화면 초기화
    ScreenConfigBuilder screen_config = GetDefaultScreenConfigBuilder();
    // screen_config.screen_width = (int)(DM.w / 1.5);
    // screen_config.screen_height = (int)(DM.h / 1.5);
    // screen_config.screen_x = DM.w / 2 - screen_config.screen_width / 2;
    // screen_config.screen_y = DM.h / 2 - screen_config.screen_height / 2;

    screen_config.screen_width = 1280;
    screen_config.screen_height = 720;
    screen_config.screen_x = DM.w / 2 - screen_config.screen_width / 2;
    screen_config.screen_y = DM.h / 2 - screen_config.screen_height / 2;

    View view;
    ERROR_HANDLER(
        CreateWindow(&view, "SuikaGame", &screen_config) != CREATE_WINDOW_SUCCESS,
        "Failed to initialize!"
    )

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

#undef ERROR_HANDLER
