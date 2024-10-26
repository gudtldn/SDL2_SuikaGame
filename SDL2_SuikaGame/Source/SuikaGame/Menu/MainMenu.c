#include "MainMenu.h"
#include "SuikaGame/GameState.h"

// forward declaration
void HandleEventMainMenu(View* view, SDL_Event* event);
void GameStartCallback(View* view);


void IntoMainMenu(View* view)
{
    // 화면 크기 가져오기
    int screen_width, screen_height;
    SDL_GetWindowSize(view->window, &screen_width, &screen_height);


    // 게임 로고 이미지 로드
    SDL_Texture* logo_texture = IMG_LoadTexture(view->renderer, "Contents/Textures/suika_game_logo.png");
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
    SDL_Texture* button_texture = IMG_LoadTexture(view->renderer, "Contents/Textures/button.png");
    if (button_texture == NULL)
    {
        LOG_ERROR(LogGame, "Failed to create button texture! SDL Error: %s", SDL_GetError());
        return;
    }

    int button_width, button_height;
    SDL_QueryTexture(button_texture, NULL, NULL, &button_width, &button_height);

    float button_origin_x = (float)(screen_width / 2 - button_width / 2);                        // 버튼의 x 좌표
    float button_origin_y = (float)(screen_height / 2 - button_height / 2 + screen_height / 12); // 버튼의 y 좌표

    SDL_FRect game_start_rect = {
        .x = button_origin_x,
        .y = button_origin_y,
        .w = (float)button_width,
        .h = (float)button_height
    };

    Button game_start_button = CreateButton(game_start_rect, button_texture);

    // 이벤트 변수 선언
    SDL_Event event;

    // frame_rate 변수 선언
    Uint32 now_time;
    Uint32 delta_time = 0;

    // 메인 메뉴 루프
    while (GetCurrentAppState() == AppState_MainMenu)
    {
        // 프레임 시작 시간
        now_time = SDL_GetTicks();

        // 이벤트 큐 핸들링
        while (SDL_PollEvent(&event) != 0)
        {
            HandleEventMainMenu(view, &event);
        }


        /****************
         * 업데이트 처리 *
         ****************/
        // 버튼 애니메이션 처리
        game_start_button.rect.y = button_origin_y + (float)(sin(now_time / 200.0) * 3);

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
        delta_time = SDL_GetTicks() - now_time;
        if (delta_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - delta_time);
        }
    }
}

void HandleEventMainMenu(View* view, SDL_Event* event)
{
    switch (event->type)
    {
    // 종료 이벤트 처리
    case SDL_QUIT:
        SetCurrentAppState(AppState_Exit);
        break;

    // 키보드 이벤트 처리
    case SDL_KEYDOWN:
        if (event->key.keysym.sym == SDLK_ESCAPE)
        {
            SetCurrentAppState(AppState_Exit);
        }
        break;

    // 윈도우 이벤트 처리
    case SDL_WINDOWEVENT:
        if (event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            Mix_ResumeMusic();
        }
        else if (event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            Mix_PauseMusic();
        }
        break;

    default:
        break;
    }
}

void GameStartCallback(View* view)
{
    LOG_DEBUG(LogGame, "Game Start Button Clicked!");
    SetCurrentAppState(AppState_Game);
}
