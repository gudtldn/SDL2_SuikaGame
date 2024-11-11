#pragma once
#include "EngineCore.h"


/// @brief 배경 오브젝트
class BackgoundObject : public GameObject
{
public:
    BackgoundObject(GameEngine* engine);

    virtual void Render(SDL_Renderer* renderer) override;
};
