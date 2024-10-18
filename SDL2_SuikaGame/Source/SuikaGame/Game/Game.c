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
    while (GetCurrentGameState() == GameState_Playing)
    {
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

    }
}

static void PauseGame(View* view)
{

}

static void GameOver(View* view)
{

}
