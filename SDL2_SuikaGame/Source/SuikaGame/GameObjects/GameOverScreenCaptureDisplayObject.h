#pragma once
#include "EnginePCH.h"


/// @brief 게임오버전 화면을 표시하는 오브젝트
class GameOverScreenCaptureDisplayObject : public GameObject
{
    /// @brief 게임오버 전 스샷을 저장 할 객체
    std::unique_ptr<Texture2D> game_over_captured_texture;

public:
    GameOverScreenCaptureDisplayObject(GameEngine* engine);

protected:
    virtual void BeginPlay() override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
