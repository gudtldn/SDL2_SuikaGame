﻿#pragma once
#include "EnginePCH.h"

// forward declaration
class FruitResource;

// delegate declaration
DECLARE_DELEGATE(FOnLandedBottomCollision);


/// @brief 과일 오브젝트
class FruitObject : public GameObject
{
private:
    /// @brief 과일 텍스처
    Texture2D* fruit_texture;

    /// @brief 과일 텍스쳐의 인덱스
    size_t fruit_idx;

    /// @brief 과일 위치
    Vector2D fruit_position;

    /// @brief 과일 오프셋 위치 (원래 위치와 과육 부분 위치의 차)
    Vector2D fruit_offset_position;

    /// @brief 과일 오프셋 크기 (꼭지 부분을 제외한, 실제 과육의 크기 오프셋)
    float fruit_offset_size;

    /// @brief 과일이 합쳐질 때 나는 소리
    Mix_Chunk* merge_sound;

    /// @brief 오브젝트 활성화 여부
    bool fruit_active;

    /// @brief 처음 땅에 닿았는지 여부
    bool is_first_landed;

    /// @brief 초기화 여부
    bool is_init;

    /// @brief BeginOverlap 이벤트 핸들
    MulticastDelegateHandle on_begin_overlap_handle;

private:
    b2BodyId fruit_body;
    b2ShapeId fruit_shape;

public:
    /// @brief 과일이 땅에 닿았을 때 발생하는 이벤트
    FOnLandedBottomCollision OnLandedBottomCollision;

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
        THROW_IF_FAILED(
            is_init,
            "FruitObject is not initialized please call InitFruit or InitRandomFruit"
        )
        if (!b2Body_IsValid(fruit_body)) return;

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
        THROW_IF_FAILED(
            is_init,
            "FruitObject is not initialized please call InitFruit or InitRandomFruit"
        )

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

    /// @brief 과일의 Body를 반환합니다.
    /// @return b2BodyId
    b2BodyId GetFruitBody() const { return fruit_body; }

    /// @brief 과일의 Shape를 반환합니다.
    /// @return b2ShapeId
    b2ShapeId GetFruitShape() const { return fruit_shape; }

    /// @brief 과일이 처음 땅에 닿았는지 여부를 반환합니다.
    bool IsFirstLanded() const { return is_first_landed; }

protected:
    virtual void BeginPlay() override;
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
    virtual void OnDestroy() override;

private:
    /// @brief this가 센서에 감지 되었는지 확인합니다.
    void CheckFruitCollisionWithBorderSensor() const;
};
