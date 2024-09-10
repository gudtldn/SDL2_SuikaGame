#include "window.h"
#include <stdio.h>

bool InitWindow(
    View* view,
    const char* title,
    const int screen_width,
    const int screen_height
) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        // 창 생성
        view->window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            screen_width,
            screen_height,
            SDL_WINDOW_SHOWN
        );

        if (view->window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            // 창 표면 가져오기
            view->screen_surface = SDL_GetWindowSurface(view->window);
        }
    }
    return true;
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
