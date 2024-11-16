#pragma once
#include "EnginePCH.h"


/// @brief BorderBottomCollisionObject는 게임의 하단 경계를 나타내는 GameObject입니다.
class BorderBottomCollisionObject : public GameObject
{
    b2BodyId border_bottom_body;
    b2ShapeId border_bottom_shape;

public:
    BorderBottomCollisionObject(GameEngine* engine);

protected:
    virtual void OnDestroy() override;
};
