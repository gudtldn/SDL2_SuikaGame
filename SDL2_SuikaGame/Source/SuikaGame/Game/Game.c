#include "Game.h"
#include "SuikaGame/GameState.h"
#include "SuikaGame/SuikaGame.h"

// 오류 핸들러
#define ERROR_HANDLER(condition, message, ...)             \
    if (condition)                                         \
    {                                                      \
        LOG_ERROR(LogGame, message, ##__VA_ARGS__);        \
        if (b2World_IsValid(world)) b2DestroyWorld(world); \
        SetCurrentAppState(AppState_Exit);                 \
        return;                                            \
    }

// forward declaration
static void SetupGame(View* view);
static void PlayingGame(View* view);
static void PauseGame(View* view);
static void GameOver(View* view);

// Box2D 세계
static b2WorldId world;


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
    LOG_DEBUG(LogGame, "SetupGame() called");

    // Box2D 세계 생성
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = (b2Vec2){0.0f, -9.8f};

    world = b2CreateWorld(&world_def);

    SetCurrentGameState(GameState_Playing);
}

static void PlayingGame(View* view)
{
    // 화면 크기 가져오기
    int screen_width, screen_height;
    SDL_GetWindowSize(view->window, &screen_width, &screen_height);

    // 테두리 배경 생성
    SDL_Texture* border_bg_texture = IMG_LoadTexture(view->renderer, "Contents/Textures/border_bg.png");
    ERROR_HANDLER(
        border_bg_texture == NULL,
        "Failed to create border texture! SDL Error: %s", IMG_GetError()
    )

    int border_bg_width, border_bg_height;
    SDL_QueryTexture(border_bg_texture, NULL, NULL, &border_bg_width, &border_bg_height);

    SDL_Rect border_bg_rect = {
        .x = (screen_width - border_bg_width) / 2,
        .y = (screen_height - border_bg_height) / 2,
        .w = border_bg_width,
        .h = border_bg_height
    };


    // 테두리 생성
    SDL_Texture* border_texture = IMG_LoadTexture(view->renderer, "Contents/Textures/border.png");
    ERROR_HANDLER(
        border_texture == NULL,
        "Failed to create border texture! SDL Error: %s", IMG_GetError()
    )

    int border_width, border_height;
    SDL_QueryTexture(border_texture, NULL, NULL, &border_width, &border_height);

    SDL_Rect border_rect = {
        .x = (screen_width - border_width) / 2,
        .y = (screen_height - border_height) / 2,
        .w = border_width,
        .h = border_height
    };

    // Box2D 경계 생성
    b2BodyDef border_body_defs[] = {
        b2DefaultBodyDef(),
        b2DefaultBodyDef(),
        b2DefaultBodyDef()
    };

#pragma region Border Body Definitions

    border_body_defs[0].type = b2_staticBody;
    border_body_defs[1].type = b2_staticBody;
    border_body_defs[2].type = b2_staticBody;

    // Left
    border_body_defs[0].position = (b2Vec2) {
        .x = (float)(screen_width / 2 - 12 - 224),
        .y = (float)(screen_height / 2 - 12 - 224)
    };

    // Right
    border_body_defs[1].position = (b2Vec2) {
        .x = (float)(screen_width / 2 + 224),
        .y = (float)(screen_height / 2 - 12 - 224)
    };

    // Bottom
    border_body_defs[2].position = (b2Vec2) {
        .x = (float)(screen_width / 2 - 224),
        .y = (float)(screen_height / 2 + 304)
    };

#pragma endregion

    b2Polygon border_polygons[] = {
        b2MakeBox(12, 552),
        b2MakeBox(12, 552),
        b2MakeBox(448, 12)
    };

    // 경계 바디 생성
    b2BodyId border_bodies[3];

    for (int i = 0; i < sizeof(border_body_defs) / sizeof(border_body_defs[0]); i++)
    {
        border_bodies[i] = b2CreateBody(world, &border_body_defs[i]);
        b2ShapeDef shape_def = b2DefaultShapeDef();
        b2CreatePolygonShape(border_bodies[i], &shape_def, &border_polygons[i]);
    }

    // 테스트 박스 생성
    SDL_Rect test_box[] = {
        { // 왼쪽
            .x = screen_width / 2 - 12 - 224,
            .y = screen_height / 2 - 12 - 224,
            .w = 12,
            .h = 552
        },
        { // 오른쪽
            .x = screen_width / 2 + 224,
            .y = screen_height / 2 - 12 - 224,
            .w = 12,
            .h = 552
        },
        { // 아래
            .x = screen_width / 2 - 224,
            .y = screen_height / 2 + 304,
            .w = 448,
            .h = 12
        }
    };

    // 이벤트 변수 선언
    SDL_Event event;

    // frame_rate 변수 선언
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

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // 마우스 좌표 가져오기
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);

                    // 마우스 좌표 출력
                    LOG_DEBUG(LogGame, "Mouse Position: (%d, %d)", mouse_x, mouse_y);
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
        RenderBackground(view->renderer, screen_width, screen_height);

        // 테두리 배경 렌더링
        SDL_RenderCopy(view->renderer, border_bg_texture, NULL, &border_bg_rect);

        // 테두리 렌더링
        SDL_RenderCopy(view->renderer, border_texture, NULL, &border_rect);

        // test_box 렌더링
        for (int i = 0; i < sizeof(test_box) / sizeof(test_box[0]); i++)
        {
            SDL_SetRenderDrawColor(view->renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(view->renderer, &test_box[i]);
        }

        // 렌더링 업데이트
        SDL_RenderPresent(view->renderer);

        // 프레임 레이트 조절
        if (delta_time < FRAME_DELAY) {
            SDL_Delay((Uint32)(FRAME_DELAY - delta_time));
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

#undef ERROR_HANDLER
