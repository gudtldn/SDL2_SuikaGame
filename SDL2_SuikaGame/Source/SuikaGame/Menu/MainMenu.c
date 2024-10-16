#include "MainMenu.h"
#include "SuikaGame/GameState.h"


void SetupMainMenu(SDL_Renderer* renderer)
{
    SDL_Event event;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                SetCurrentAppState(AppState_Exit);
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}
