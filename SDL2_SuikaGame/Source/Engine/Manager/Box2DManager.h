#pragma once
#include "Engine/EngineTypes/Vector2D.h"
#include <box2d/box2d.h>


/// @brief Box2D manager
class Box2DManager
{
private:
    b2WorldId world_id;

public:
    Box2DManager();
    ~Box2DManager();


    /****** Getter && Setter ******/

    /// @brief Box2D의 WorldID를 가져옵니다.
    [[nodiscard]] b2WorldId GetWorldID() const { return world_id; }

    /// @brief 월드의 중력을 가져옵니다.
    [[nodiscard]] inline Vector2D GetGravity() const;

    /// @brief 월드의 중력을 설정합니다.
    /// @param gravity 중력
    inline void SetGravity(Vector2D gravity) const;
};
