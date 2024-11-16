#pragma once
#include "EnginePCH.h"

class FruitResourceObject;


/// @brief 과일 오브젝트
class FruitObject : public GameObject
{
private:
    /// @brief 과일 텍스처
    Texture2D* fruit_texture;

    /// @brief 과일 위치
    Vector2D fruit_position;

    /// @brief 과일 오프셋 위치
    Vector2D fruit_offset_position;

    /// @brief 과일 오프셋 크기
    float fruit_offset_size;

    /// @brief 오브젝트 활성화 여부
    bool fruit_active;

    /// @brief 초기화 여부
    bool is_init;

private:
    b2BodyId fruit_body;
    b2ShapeId fruit_shape;

public:
    FruitObject(GameEngine* engine);

    /// @brief 과일을 초기화합니다.
    /// @param idx 과일 인덱스
    void InitFruit(size_t idx);

    /// @brief 랜덤한 과일을 초기화합니다. (0 ~ 4)
    void InitRandomFruit();

    /// @brief 과일의 위치를 반환합니다.
    /// @return 과일의 위치
    Vector2D GetFruitPosition() const { return fruit_position; }

    /// @brief 과일의 위치를 설정합니다. (이미지 크기 / 2 해서)
    /// @param new_position 새로운 위치
    void SetFruitPosition(Vector2D new_position)
    {
        THROW_IF_FAILED(is_init);
        fruit_position = new_position;
        b2Body_SetTransform(
            fruit_body,
            {
                new_position.X,
                new_position.Y
            },
            b2Body_GetRotation(fruit_body)
        );
    }

    /// @brief 과일이 활성화되어 있는지 반환합니다.
    /// @return 활성화 여부
    bool GetFruitActive() const { return fruit_active; }

    /// @brief 과일을 활성화합니다.
    /// @param new_value 새로운 활성화 여부
    void SetFruitActive(bool new_value)
    {
        THROW_IF_FAILED(is_init);

        fruit_active = new_value;
        if (new_value)
        {
            b2Body_Enable(fruit_body);
        }
        else
        {
            b2Body_Disable(fruit_body);
        }
    }

protected:
    virtual void BeginPlay() override;
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
    virtual void OnDestroy() override;
};
