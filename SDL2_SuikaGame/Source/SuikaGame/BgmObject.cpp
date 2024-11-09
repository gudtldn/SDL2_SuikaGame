#include "BgmObject.h"


void BgmObject::BeginPlay()
{
    // BGM 로드
    LOG_INFO("Loading bgm...");
    bgm.reset(Mix_LoadMUS("Contents/Sounds/suika_game_bgm.mp3"));
    if (!bgm)
    {
        LOG_WARN("Failed to load bgm! SDL_mixer Error: %s", Mix_GetError());
    }

    // BGM 재생
    LOG_INFO("Playing bgm...");
    if (Mix_PlayMusic(bgm.get(), -1) == -1)
    {
        LOG_WARN("Failed to play bgm! SDL_mixer Error: %s", Mix_GetError());
    }
}
