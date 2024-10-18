#include "MainMenu.h"
#include "SuikaGame/GameState.h"


void IntoMainMenu(View* view)
{
    SDL_Event event;

    // frame_rate 변수 선언
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    int frame_time;

    // 메인 메뉴 루프
    while (GetCurrentAppState() == AppState_MainMenu)
    {
        // 프레임 시작 시간
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

        // const Uint8* key_state = SDL_GetKeyboardState(NULL);
        // LOG_INFO(
        //     LogGame,
        //     "w: %d, a: %d, s: %d, d: %d\r",
        //     key_state[SDL_SCANCODE_W],
        //     key_state[SDL_SCANCODE_A],
        //     key_state[SDL_SCANCODE_S],
        //     key_state[SDL_SCANCODE_D]
        // );


        /**************
         * 렌더링 처리 *
         **************/
        // 렌더링 색상 설정
        SDL_SetRenderDrawColor(view->renderer, 0xFF, 0x00, 0xFF, 0xFF);

        // 화면 지우기
        SDL_RenderClear(view->renderer);

        // 화면 업데이트
        SDL_RenderPresent(view->renderer);

        // 프레임 레이트 제어
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }
    }
}
