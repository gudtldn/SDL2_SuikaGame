#pragma once
#include "EnginePCH.h"

class FruitResourceObject;


/// @brief 과일 오브젝트
class FruitObject : public GameObject
{
    const Texture2D* fruit_texture;
    Vector2D fruit_position;
    Vector2D fruit_offset_position;
    float fruit_offset_size;

public:
    FruitObject(GameEngine* engine);

    /// @brief 과일의 위치를 반환합니다.
    /// @return 과일의 위치
    Vector2D GetFruitPosition() const { return fruit_position; }

    /// @brief 과일의 위치를 설정합니다.
    /// @param new_position 새로운 위치
    void SetFruitPosition(Vector2D new_position) { fruit_position = new_position; }

    /// @brief 과일의 텍스처 크기를 반환합니다.
    Vector2D GetFruitSize() const { return fruit_texture->GetSize(); }

protected:
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
