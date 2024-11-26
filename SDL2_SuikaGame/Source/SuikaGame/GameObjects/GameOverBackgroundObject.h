#pragma once
#include "EnginePCH.h"


class GameOverBackgroundObject : public GameObject
{
    // 검은색 반투명 배경
    Rectangle background_rect;

    // 게임오버 배경 이미지
    std::unique_ptr<Texture2D> background_texture;

public:
    GameOverBackgroundObject(GameEngine* engine);

protected:
    virtual void Render(SDL_Renderer* renderer) const override;
};
