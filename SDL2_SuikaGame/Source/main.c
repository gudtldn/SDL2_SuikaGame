#include "Core.h"

// https://lazyfoo.net/tutorials/SDL/index.php

int main(int argc, char* args[])
{
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR(LogGame, "SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    // Screen Size 가져오기
    SDL_DisplayMode DM;
    if (SDL_GetCurrentDisplayMode(0, &DM) != 0)
    {
        LOG_ERROR(LogGame, "SDL_GetCurrentDisplayMode failed: %s", SDL_GetError());
        return -1;
    }

    // 화면 초기화
    ScreenConfigBuilder screen_config = GetDefaultScreenConfigBuilder();
    screen_config.screen_width = (int)(DM.w / 1.5);
    screen_config.screen_height = (int)(DM.h / 1.5);
    screen_config.screen_x = DM.w / 2 - screen_config.screen_width / 2;
    screen_config.screen_y = DM.h / 2 - screen_config.screen_height / 2;

    View view;
    if (CreateWindow(&view, "SuikaGame", &screen_config) != CREATE_WINDOW_SUCCESS)
    {
        LOG_ERROR(LogGame, "Failed to initialize!");
        return -1;
    }

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        // 이벤트 큐 핸들링
        while (SDL_PollEvent(&event) != 0)
        {
            // user request quit
            if (event.type == SDL_QUIT)
                quit = true;

            // user press key
            else if (event.type == SDL_KEYDOWN)
            {
                EBindingKey key = GetPressedKey(&event);
                if (key == KEY_ESCAPSE)
                    quit = true;

                LOG_INFO(LogGame, "Key press detected: %d", key);
            }
        }

        SDL_FillRect(view.screen_surface, NULL, SDL_MapRGB(view.screen_surface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(view.window);
    }

    CloseWindow(&view);
    return 0;
}
