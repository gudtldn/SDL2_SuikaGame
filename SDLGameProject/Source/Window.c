#include "window.h"
#include "LogSystem.h"

// Core.h에 정의된 로그 카테고리
extern const char* LogGame;

CreateWindowResult CreateWindow(
    View* view,
    const char* title,
    const ScreenConfigBuilder* screen_config
) {
    // SDL 초기화 여부 확인
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        // SDL 초기화
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            LOG_ERROR(LogGame, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
            return CREATE_WINDOW_FAIL_SDL_INIT;
        }
    }

    // 창 생성
    view->window = SDL_CreateWindow(
        title,
        screen_config->screen_x,
        screen_config->screen_y,
        screen_config->screen_width,
        screen_config->screen_height,
        SDL_WINDOW_SHOWN
    );
    if (view->window == NULL)
    {
        LOG_ERROR(LogGame, "Window could not be created! SDL_Error: %s", SDL_GetError());
        return CREATE_WINDOW_FAIL_CREATE_WINDOW;
    }

    // 창 표면 가져오기
    view->screen_surface = SDL_GetWindowSurface(view->window);
    if (view->screen_surface == NULL)
    {
        LOG_ERROR(LogGame, "Window surface could not be created! SDL_Error: %s", SDL_GetError());
        return CREATE_WINDOW_FAIL_GET_WINDOW_SURFACE;
    }

    return CREATE_WINDOW_SUCCESS;
}

/// @brief 창 닫기
void CloseWindow(View* view)
{
    // 창 Surface 해제
    SDL_FreeSurface(view->screen_surface);
    view->screen_surface = NULL;

    // Window 해제
    SDL_DestroyWindow(view->window);
    view->window = NULL;

    // SDL 종료
    SDL_Quit();
}

ScreenConfigBuilder GetDefaultScreenConfigBuilder()
{
    ScreenConfigBuilder builder = { 0, 0, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED };
    return builder;
}
