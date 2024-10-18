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

    // frame_rate 변수 선언
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    int frame_time;

    // 프로그램 루프
    SetCurrentAppState(AppState_MainMenu);
    while (GetCurrentAppState() != AppState_Exit)
    {
        int frame_start = SDL_GetTicks();

        // 프로그램 상태에 따른 처리
        switch (GetCurrentAppState())
        {
        case AppState_MainMenu:
            UpdateMainMenu(&view);
            RenderMainMenu(&view);
            break;
        case AppState_Game:
            UpdateGame(&view);
            RenderGame(&view);
            break;
        }

        // 화면 지우기
        SDL_RenderClear(view.renderer);

        // 화면 업데이트
        SDL_RenderPresent(view.renderer);

        // 프레임 레이트 제어
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    CloseWindow(&view);
    return 0;
}
