#pragma once
#include "EnginePCH.h"


/// @brief 다음 과일을 보여주는 DisplayObject
class NextFruitDisplayObject : public GameObject
{
    /// @brief 버블 텍스처
    std::unique_ptr<Texture2D> bubble_texture;

    /// @brief 텍스트 텍스처
    std::unique_ptr<Texture2D> text_texture;

    /// @brief 버블의 위치
    Vector2D display_position;

    Texture2D* display_fruit_texture;

public:
    NextFruitDisplayObject(GameEngine* engine);

protected:
    virtual void BeginPlay() override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
