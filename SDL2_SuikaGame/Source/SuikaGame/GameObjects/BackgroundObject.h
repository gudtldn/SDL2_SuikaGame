#pragma once
#include "EnginePCH.h"


/// @brief 배경 오브젝트
class BackgroundObject : public GameObject
{
private:
    /// @brief 배경 색상
    SDL_Color background_color;


    /// @brief 배경 하이라이트 Rect
    SDL_Rect second_background_rect;

    /// @brief 배경 하이라이트 색상
    SDL_Color second_background_color;

public:
    BackgroundObject(GameEngine* engine);

protected:
    virtual void Render(SDL_Renderer* renderer) const override;
};
