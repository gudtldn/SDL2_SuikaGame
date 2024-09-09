#include "Window.h"
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{
    View view;
    if (!InitWindow(&view, "SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        SDL_FillRect(view.screen_surface, NULL, SDL_MapRGB(view.screen_surface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(view.window);
        SDL_Delay(2000);
    }

    CloseWindow(&view);
    return 0;
}
