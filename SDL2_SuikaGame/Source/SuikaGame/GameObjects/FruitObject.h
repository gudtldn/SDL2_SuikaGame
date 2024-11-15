#pragma once
#include "EnginePCH.h"

class FruitResourceObject;


/// @brief 과일 오브젝트
class FruitObject : public GameObject
{
    /// @brief 과일 텍스처
    const Texture2D* fruit_texture;

    /// @brief 과일 위치
    Vector2D fruit_position;

    /// @brief 과일 오프셋 위치
    Vector2D fruit_offset_position;

    /// @brief 과일 오프셋 크기
    float fruit_offset_size;

    /// @brief 오브젝트 활성화 여부
    bool fruit_active;

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

    /// @brief 과일이 활성화되어 있는지 반환합니다.
    /// @return 활성화 여부
    bool GetFruitActive() const { return fruit_active; }

    /// @brief 과일을 활성화합니다.
    /// @param new_value 새로운 활성화 여부
    void SetFruitActive(bool new_value) { fruit_active = new_value; }

protected:
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
