#include "Window.h"
#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main()
{
    View view;
    if (!InitWindow(&view, "SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        printf("Failed to initialize!");
        return -1;
    }

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        // // 이벤트 큐 핸들링
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = true;
        }

        SDL_FillRect(view.screen_surface, NULL, SDL_MapRGB(view.screen_surface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(view.window);
    }

    CloseWindow(&view);
    return 0;
}
