#pragma once
#include "EnginePCH.h"


class BorderTopSensorObject : public GameObject
{
    b2BodyId border_sensor_body;
    b2ShapeId border_sensor_shape;

    MulticastDelegateHandle begin_sensor_overlap_handle;
    MulticastDelegateHandle end_sensor_overlap_handle;

public:
    BorderTopSensorObject(GameEngine* engine);

    b2BodyId GetSensorBody() const { return border_sensor_body; }
    b2ShapeId GetSensorShape() const { return border_sensor_shape; }

protected:
    virtual void BeginPlay() override;
    virtual void OnDestroy() override;
};
