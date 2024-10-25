#include "MainMenu.h"
#include "SuikaGame/GameState.h"

// forward declaration
void GameStartCallback(View* view);


void IntoMainMenu(View* view)
{
    // 화면 크기 가져오기
    int screen_width, screen_height;
    SDL_GetWindowSize(view->window, &screen_width, &screen_height);


    // 게임 로고 이미지 로드
    SDL_Surface* logo_surface = IMG_Load("Contents/Textures/suika_game_logo.png");
    if (logo_surface == NULL)
    {
        LOG_ERROR(LogGame, "Failed to load logo image! SDL_image Error: %s", IMG_GetError());
        return;
    }

    SDL_Texture* logo_texture = SDL_CreateTextureFromSurface(view->renderer, logo_surface);
    SDL_FreeSurface(logo_surface);
    if (logo_texture == NULL)
    {
        LOG_ERROR(LogGame, "Failed to create logo texture! SDL Error: %s", SDL_GetError());
        return;
    }

    // 로고 이미지 위치 설정
    int logo_width, logo_height;
    SDL_QueryTexture(logo_texture, NULL, NULL, &logo_width, &logo_height);

    SDL_Rect logo_rect = {
        .x = screen_width / 2 - logo_width / 2,
        .y = (screen_height / 2 - logo_height / 2) - screen_height / 4,
        .w = logo_width,
        .h = logo_height
    };


    // GameStart 버튼 생성
    SDL_Surface* button_surface = IMG_Load("Contents/Textures/button.png");
    if (button_surface == NULL)
    {
        LOG_ERROR(LogGame, "Failed to load button image! SDL_image Error: %s", IMG_GetError());
        return;
    }

    SDL_Texture* button_texture = SDL_CreateTextureFromSurface(view->renderer, button_surface);
    SDL_FreeSurface(button_surface);
    if (button_texture == NULL)
    {
        LOG_ERROR(LogGame, "Failed to create button texture! SDL Error: %s", SDL_GetError());
        return;
    }

    int button_width, button_height;
    SDL_QueryTexture(button_texture, NULL, NULL, &button_width, &button_height);

    int button_origin_x = screen_width / 2 - button_width / 2;                        // 버튼의 x 좌표
    int button_origin_y = screen_height / 2 - button_height / 2 + screen_height / 12; // 버튼의 y 좌표

    SDL_Rect game_start_rect = {
        .x = button_origin_x,
        .y = button_origin_y,
        .w = button_width,
        .h = button_height
    };

    Button game_start_button = CreateButton(game_start_rect, button_texture);

    // 이벤트 변수 선언
    SDL_Event event;

    // frame_rate 변수 선언
    double delta_time = 0.0;

    Uint64 now_time = 0;
    Uint64 last_time = 0;

    // 메인 메뉴 루프
    while (GetCurrentAppState() == AppState_MainMenu)
    {
        // 프레임 시작 시간
        now_time = SDL_GetPerformanceCounter();
        delta_time = (double)(now_time - last_time) / (double)SDL_GetPerformanceFrequency();

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
        // 버튼 애니메이션 처리
        game_start_button.rect.y = button_origin_y + (int)(sin(now_time / 2000000.0) * 3);

        // 버튼 클릭 이벤트 처리
        UpdateHandleButton(view, &game_start_button, GameStartCallback);


        /**************
         * 렌더링 처리 *
         **************/

        // 배경 채우기
        SDL_SetRenderDrawColor(view->renderer, 0xDD, 0x8E, 0x40, 0xFF);
        SDL_RenderClear(view->renderer);

        // 로고 이미지 렌더링
        SDL_RenderCopy(view->renderer, logo_texture, NULL, &logo_rect);

        // GameStartButton 렌더링
        RenderButton(view->renderer, &game_start_button);

        // 화면 업데이트
        SDL_RenderPresent(view->renderer);

        // 프레임 레이트 제어
        if (delta_time < FRAME_DELAY) {
            SDL_Delay((Uint32)(FRAME_DELAY - delta_time));
        }
        last_time = now_time;
    }
}

void GameStartCallback(View* view)
{
    LOG_DEBUG(LogGame, "Game Start Button Clicked!");
    SetCurrentAppState(AppState_Game);
}
