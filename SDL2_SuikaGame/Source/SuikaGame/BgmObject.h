#pragma once
#include "EngineCore.h"

/// @brief BGM 오브젝트
class BgmObject : public GameObject, public IEventObserver
{
private:
    std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> bgm;

public:
    BgmObject()
        : bgm(nullptr, Mix_FreeMusic)
    {
    }

    // 오브젝트 생성 시 호출됩니다.
    virtual void BeginPlay() override;

    // IEventObserver
    virtual void OnEvent(const SDL_Event& event) override;
    // ~IEventObserver
};
