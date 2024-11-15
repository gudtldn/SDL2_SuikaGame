#pragma once
#include "EnginePCH.h"


/// @brief 다음 과일을 보여주는 DisplayObject
class NextFruitDisplayObject : public GameObject
{
    std::unique_ptr<Texture2D> bubble_texture;
    Vector2D bubble_position;

    Texture2D* display_fruit_texture;

public:
    NextFruitDisplayObject(GameEngine* engine);

protected:
    virtual void BeginPlay() override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
