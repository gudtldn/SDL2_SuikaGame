#pragma once
#include "EnginePCH.h"


/// @brief 게임 로고 오브젝트
class GameLogoObject : public GameObject
{
private:
    std::unique_ptr<FTexture2D> logo_texture;

public:
    GameLogoObject(GameEngine* engine);

protected:
    virtual void Render(SDL_Renderer* renderer) const override;
};
