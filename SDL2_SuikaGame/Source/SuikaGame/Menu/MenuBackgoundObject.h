#pragma once
#include "EngineCore.h"


/// @brief 메인메뉴 배경 오브젝트
class MenuBackgoundObject : public GameObject
{
private:
    std::unique_ptr<Texture> logo_texture;

public:
    MenuBackgoundObject(GameEngine* engine);

    virtual void Render(SDL_Renderer* renderer) override;
};
