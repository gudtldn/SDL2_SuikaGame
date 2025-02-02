#pragma once
#include "EnginePCH.h"


/// @brief BGM 오브젝트
class BgmObject : public GameObject
{
private:
    std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> bgm;

public:
    BgmObject(GameEngine* engine);

protected:
    // 오브젝트 생성 시 호출됩니다.
    virtual void BeginPlay() override;

    // SDL 이벤트 발생 시 호출됩니다.
    virtual void OnEvent(const SDL_Event& event) override;
};
