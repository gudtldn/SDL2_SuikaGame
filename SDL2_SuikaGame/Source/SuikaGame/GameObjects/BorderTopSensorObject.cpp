#include "BorderTopSensorObject.h"
#include "SuikaGame/Stages/GameStage.h"
#include "SuikaGame/GameObjects/BorderObject.h"


BorderTopSensorObject::BorderTopSensorObject(GameEngine* engine)
    : GameObject(engine)
{
    std::vector<BorderObject*> borders;
    GetCurrentStage()->GetObjectManager().GetGameObjectsOfClass<BorderObject>(borders);
    THROW_IF_FAILED(
        !borders.empty(),
        "Failed to find BorderObject in the current stage"
    )
    const BorderObject* border_obj = borders.front();
    const Vector2D texture_position = border_obj->GetObjectPosition();

    SDL_FRect top_offset = {
        .x = 0.0f,
        .y = -272.0f,
        .w = 224.0f,
        .h = 8.0f
    };

    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_staticBody;
    body_def.position = {
        .x = texture_position.X + top_offset.x,
        .y = texture_position.Y + top_offset.y
    };
    body_def.userData = this;
    border_sensor_body = b2CreateBody(
        dynamic_cast<GameStage*>(GetCurrentStage())->GetBox2DManager().GetWorldID(),
        &body_def
    );

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.isSensor = true;
    shape_def.userData = this;

    b2Polygon border_polygon = b2MakeBox(top_offset.w, top_offset.h);
    border_sensor_shape = b2CreatePolygonShape(border_sensor_body, &shape_def, &border_polygon);
}

void BorderTopSensorObject::OnDestroy()
{
    b2DestroyShape(border_sensor_shape);
    b2DestroyBody(border_sensor_body);

    border_sensor_shape = b2_nullShapeId;
    border_sensor_body = b2_nullBodyId;
}
