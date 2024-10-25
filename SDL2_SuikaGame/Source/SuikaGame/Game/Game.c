#include "Game.h"
#include "SuikaGame/GameState.h"

static void SetupGame(View* view);
static void PlayingGame(View* view);
static void PauseGame(View* view);
static void GameOver(View* view);

void IntoGame(View* view)
{
    // 게임 루프
    while (GetCurrentAppState() == AppState_Game)
    {
        switch (GetCurrentGameState())
        {
        case GameState_Setup:
            SetupGame(view);
            break;
        case GameState_Playing:
            PlayingGame(view);
            break;
        case GameState_Pause:
            PauseGame(view);
            break;
        case GameState_GameOver:
            GameOver(view);
            break;
        }
    }
}

static void SetupGame(View* view)
{
    SetCurrentGameState(GameState_Playing);
}

static void PlayingGame(View* view)
{
    SDL_Event event;

    // frame_rate 변수 선언
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    double delta_time = 0.0;

    Uint64 now_time = 0;
    Uint64 last_time = 0;

    while (
        GetCurrentAppState() == AppState_Game
        && GetCurrentGameState() == GameState_Playing
    ) {
        now_time = SDL_GetPerformanceCounter();
        delta_time = (double)((now_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency());

        // 이벤트 큐 핸들링
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            // 종료 이벤트 처리
            case SDL_QUIT:
                SetCurrentAppState(AppState_Exit);
                break;

            // 키보드 이벤트 처리
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SetCurrentAppState(AppState_Exit);
                }
                break;

            // 윈도우 이벤트 처리
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                {
                    Mix_ResumeMusic();
                }
                else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                {
                    Mix_PauseMusic();
                }
                break;

            default:
                break;
            }
        }

        /****************
         * 업데이트 처리 *
         ****************/

        /**************
         * 렌더링 처리 *
         **************/

        // 배경색 설정
        SDL_SetRenderDrawColor(view->renderer, 0xDD, 0x8E, 0x40, 0xFF);
        SDL_RenderClear(view->renderer);

        // 렌더링 업데이트
        SDL_RenderPresent(view->renderer);

        // 프레임 레이트 조절
        if (delta_time < frame_delay) {
            SDL_Delay((Uint32)(frame_delay - delta_time));
        }
        last_time = now_time;
    }
}

static void PauseGame(View* view)
{

}

static void GameOver(View* view)
{

}
