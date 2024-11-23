#pragma once
#include "EnginePCH.h"

// forward declaration
class FruitObject;


/// @brief 다음 과일을 보여주는 DisplayObject
class NextFruitDisplayObject : public GameObject
{
    /// @brief 버블 텍스처
    std::unique_ptr<Texture2D> bubble_texture;

    /// @brief 텍스트 텍스처
    std::unique_ptr<Texture2D> text_texture;

    /// @brief 다음 과일
    FruitObject* display_fruit;

    /// @brief 버블의 위치
    Vector2D display_position;

    /// @brief 원래 위치
    Vector2D origin;

    /// @brief 애니메이션에 사용될 랜덤 오프셋
    float random_offset;

public:
    NextFruitDisplayObject(GameEngine* engine);

protected:
    virtual void BeginPlay() override;
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
