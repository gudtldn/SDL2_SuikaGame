#include "MainMenu.h"
#include "SuikaGame/GameState.h"


void IntoMainMenu(View* view)
{
    SDL_Event event;

    // frame_rate 변수 선언
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;
    double delta_time = 0.0;

    Uint64 now_time = 0;
    Uint64 last_time = 0;

    // 메인 메뉴 루프
    while (GetCurrentAppState() == AppState_MainMenu)
    {
        // 프레임 시작 시간
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

        // 버튼 위치 업데이트
        int screen_width, screen_height;
        SDL_GetWindowSize(view->window, &screen_width, &screen_height);
        GameStartButton.x = screen_width / 2 - GameStartButton.w / 2;
        GameStartButton.y = screen_height / 2 - GameStartButton.h / 2;

        // 버튼 클릭 이벤트 처리
        int mouse_x, mouse_y;
        Uint32 state = SDL_GetMouseState(&mouse_x, &mouse_y);
        if (mouse_x >= GameStartButton.x && mouse_x <= GameStartButton.x + GameStartButton.w &&
            mouse_y >= GameStartButton.y && mouse_y <= GameStartButton.y + GameStartButton.h)
        {
            if (state & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SetCurrentAppState(AppState_Game);
            }
        }


        /**************
         * 렌더링 처리 *
         **************/

        // 배경을 흰색으로 채우기
        SDL_SetRenderDrawColor(view->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(view->renderer);

        // GameStartButton 렌더링
        SDL_SetRenderDrawColor(view->renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(view->renderer, &GameStartButton);

        // 화면 업데이트
        SDL_RenderPresent(view->renderer);

        // 프레임 레이트 제어
        if (delta_time < frame_delay) {
            SDL_Delay((Uint32)(frame_delay - delta_time));
        }
        last_time = now_time;
    }
}
