#pragma once
#include "EngineCore.h"


/// @brief 배경 오브젝트
class BackgoundObject : public GameObject
{
private:
    /// @brief 배경 색상
    SDL_Color background_color;


    /// @brief 배경 하이라이트 Rect
    SDL_Rect second_background_rect;

    /// @brief 배경 하이라이트 색상
    SDL_Color second_background_color;

public:
    BackgoundObject(GameEngine* engine);

    virtual void Render(SDL_Renderer* renderer) override;
};
