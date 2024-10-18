#include "MainMenu.h"
#include "SuikaGame/GameState.h"


void UpdateMainMenu(View* view)
{
    SDL_Event event;

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

    // const Uint8* key_state = SDL_GetKeyboardState(NULL);
    // LOG_INFO(
    //     LogGame,
    //     "w: %d, a: %d, s: %d, d: %d\r",
    //     key_state[SDL_SCANCODE_W],
    //     key_state[SDL_SCANCODE_A],
    //     key_state[SDL_SCANCODE_S],
    //     key_state[SDL_SCANCODE_D]
    // );
}

void RenderMainMenu(View* view)
{
    // 렌러링 색상 설정
    SDL_SetRenderDrawColor(view->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}
