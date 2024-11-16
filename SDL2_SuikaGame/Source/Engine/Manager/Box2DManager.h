#pragma once
#include "Engine/EngineTypes/Vector2D.h"
#include "Engine/Utils/DelegateCombination.h"
#include <box2d/box2d.h>

// forward declaration
class GameObject;

// delegate declaration
DECLARE_MULTICAST_DELEGATE_TwoParams(
    FBeginOverlapDelegate,
    GameObject* a,
    GameObject* b
)

DECLARE_MULTICAST_DELEGATE_TwoParams(
    FEndOverlapDelegate,
    GameObject* a,
    GameObject* b
)

DECLARE_MULTICAST_DELEGATE_TwoParams(
    FOnHitDelegate,
    GameObject* a,
    GameObject* b
)


/// @brief Box2D manager
class Box2DManager
{
private:
    b2WorldId world_id;

public:
    Box2DManager();
    ~Box2DManager();


    /****** Delegate ******/
    FBeginOverlapDelegate OnBeginOverlap;
    FEndOverlapDelegate OnEndOverlap;
    FOnHitDelegate OnHit;


    /****** Getter && Setter ******/

    /// @brief Box2D의 WorldID를 가져옵니다.
    [[nodiscard]] b2WorldId GetWorldID() const { return world_id; }

    /// @brief World를 시뮬레이션합니다.
    /// @param time_step 시뮬레이션할 시간, 보통은 1/60을 사용합니다.
    /// @param sub_step_count 서브 스텝의 수, 서브 스텝의 수를 늘리면 정확도가 높아집니다. 일반적으로 4를 사용합니다.
    void Step(float time_step, int sub_step_count) const;

    /// @brief 월드의 중력을 가져옵니다.
    [[nodiscard]] inline Vector2D GetGravity() const;

    /// @brief 월드의 중력을 설정합니다.
    /// @param gravity 중력
    inline void SetGravity(Vector2D gravity) const;
};
