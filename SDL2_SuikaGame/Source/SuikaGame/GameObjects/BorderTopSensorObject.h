#pragma once
#include "EnginePCH.h"


class BorderTopSensorObject : public GameObject
{
    b2BodyId border_sensor_body;
    b2ShapeId border_sensor_shape;

public:
    BorderTopSensorObject(GameEngine* engine);

protected:
    virtual void OnDestroy() override;
};
