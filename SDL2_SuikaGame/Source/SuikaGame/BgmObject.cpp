#include "BgmObject.h"


void BgmObject::BeginPlay()
{
    bgm.reset(Mix_LoadMUS("Contents/Sounds/suika_game_bgm.mp3"));
    if (bgm == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load bgm! SDL_mixer Error: %s", Mix_GetError());
    }

    // BGM 재생
    if (Mix_PlayMusic(bgm.get(), -1) == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to play bgm! SDL_mixer Error: %s", Mix_GetError());
    }
}

BgmObject::~BgmObject()
{
    // BGM 해제
    if (bgm != nullptr)
    {
        Mix_FreeMusic(bgm.get());
    }
}
