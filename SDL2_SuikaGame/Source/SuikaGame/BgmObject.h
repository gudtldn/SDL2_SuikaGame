#pragma once
#include "EngineCore.h"
#include <memory>

/// @brief BGM 오브젝트
class BgmObject : public GameObject
{
private:
    std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> bgm;

public:
    BgmObject()
        : bgm(nullptr, Mix_FreeMusic) {}
    virtual ~BgmObject() = default;

    virtual void BeginPlay() override;
};
