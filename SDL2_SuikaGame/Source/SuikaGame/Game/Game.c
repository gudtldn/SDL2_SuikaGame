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
    int frame_time;

    while (
        GetCurrentAppState() == AppState_Game
        && GetCurrentGameState() == GameState_Playing
    ) {
        int frame_start = SDL_GetTicks();

        // 이벤트 큐 핸들링
        while (SDL_PollEvent(&event) != 0)
        {
            // user request quit
            if (event.type == SDL_QUIT)
                SetCurrentAppState(AppState_Exit);

            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                SetCurrentAppState(AppState_Exit);
            }
        }

        /****************
         * 업데이트 처리 *
         ****************/

        /**************
         * 렌더링 처리 *
         **************/

        // 흰색으로 지우기
        SDL_SetRenderDrawColor(view->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(view->renderer);

        // 렌더링 업데이트
        SDL_RenderPresent(view->renderer);

        // 프레임 레이트 조절
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }
    }
}

static void PauseGame(View* view)
{

}

static void GameOver(View* view)
{

}
