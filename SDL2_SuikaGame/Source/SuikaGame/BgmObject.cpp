#include "BgmObject.h"

BgmObject::BgmObject(GameEngine* engine)
    : GameObject(engine)
    , bgm(nullptr, Mix_FreeMusic)
{
}

void BgmObject::BeginPlay()
{
    // BGM 로드
    LOG_DEBUG("Loading bgm...");
    bgm.reset(Mix_LoadMUS("Contents/Sounds/suika_game_bgm.mp3"));
    if (!bgm)
    {
        LOG_WARN("Failed to load bgm! SDL_mixer Error: {}", Mix_GetError());
    }

    // BGM 재생
    LOG_DEBUG("Playing bgm...");
    if (Mix_PlayMusic(bgm.get(), -1) == -1)
    {
        LOG_WARN("Failed to play bgm! SDL_mixer Error: {}", Mix_GetError());
    }
}

void BgmObject::OnEvent(const SDL_Event& event)
{
    if (event.type == SDL_WINDOWEVENT)
    {
        // 창이 활성화되었을 때
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            // BGM 재생
            LOG_DEBUG("Resuming bgm...");
            Mix_ResumeMusic();
        }

        // 창이 비활성화되었을 때
        else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            // BGM 일시정지
            LOG_DEBUG("Pausing bgm...");
            Mix_PauseMusic();
        }
    }
}
