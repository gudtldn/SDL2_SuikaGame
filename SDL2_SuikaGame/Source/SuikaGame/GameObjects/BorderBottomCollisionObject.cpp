#include "BorderBottomCollisionObject.h"
#include "SuikaGame/Stages/GameStage.h"
#include "SuikaGame/GameObjects/BorderObject.h"


BorderBottomCollisionObject::BorderBottomCollisionObject(GameEngine* engine)
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

    // 다른 Rect는 BorderObject에 있음
    SDL_FRect bottom_offset = {
        .x = 0.0f,
        .y = 312.0f,
        .w = 224.0f,
        .h = 8.0f
    };

    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_staticBody;
    body_def.position = {
        .x = texture_position.X + bottom_offset.x,
        .y = texture_position.Y + bottom_offset.y
    };
    border_bottom_body = b2CreateBody(
        dynamic_cast<GameStage*>(GetCurrentStage())->GetBox2DManager().GetWorldID(),
        &body_def
    );
    b2Body_SetUserData(border_bottom_body, this);

    b2Polygon border_polygon = b2MakeBox(bottom_offset.w, bottom_offset.h);
    b2ShapeDef border_shape_def = b2DefaultShapeDef();
    border_bottom_shape = b2CreatePolygonShape(border_bottom_body, &border_shape_def, &border_polygon);
}

void BorderBottomCollisionObject::OnDestroy()
{
    b2DestroyShape(border_bottom_shape);
    b2DestroyBody(border_bottom_body);

    border_bottom_shape = b2_nullShapeId;
    border_bottom_body = b2_nullBodyId;
}
