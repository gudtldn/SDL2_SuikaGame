#pragma once
#include <SDL.h>
#include <stdbool.h>

/// @brief 화면 정보
typedef struct View
{
    SDL_Window* window;
    SDL_Surface* screen_surface;
} View;


bool InitWindow(
    View* view,
    const char* title,
    const int screen_width,
    const int screen_height
);
void CloseWindow(View* view);
