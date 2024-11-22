#include "BorderTopSensorObject.h"
#include "SuikaGame/Stages/GameStage.h"
#include "SuikaGame/GameObjects/BorderObject.h"
#include "SuikaGame/GameObjects/FruitObject.h"


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
        .y = -280.0f,
        .w = 224.0f,
        .h = 16.0f
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

void BorderTopSensorObject::BeginPlay()
{
    // TODO: 조건식을 수정해야함
    // 처음에 센서에 감지가 되는데, 감지된 상태로 FirstLanded가 true로 되면 게임 오버가 안됨
    GameStage* game_stage = dynamic_cast<GameStage*>(GetCurrentStage());
    begin_sensor_overlap_handle = game_stage->GetBox2DManager()
        .OnBeginSensorOverlap.AddFunction([this, game_stage](GameObject* visitor)
    {
        if (const FruitObject* fruit_obj = dynamic_cast<FruitObject*>(visitor))
        {
            if (fruit_obj->IsFirstLanded()) 
            {
                game_stage->SetGameOver(true);
                // TODO: 3초 타이머 작동 후, 아직도 Overlap되어있으면, 게임 오버
            }
        }
    });

    end_sensor_overlap_handle = game_stage->GetBox2DManager()
        .OnEndSensorOverlap.AddFunction([this, game_stage](GameObject* visitor)
    {
        if (
            const FruitObject* fruit_obj = dynamic_cast<FruitObject*>(visitor);
            fruit_obj && fruit_obj->IsFirstLanded()
        ) {
            // game_stage->SetGameOver(false);
            // TODO: 3초 타이머 취소
        }
    });
}

#pragma region DebugDraw
void BorderTopSensorObject::Render(SDL_Renderer* renderer) const
{
    // b2PolygonShape에서 정점 정보 가져오기
    auto [x, y] = b2Body_GetPosition(border_sensor_body);
    const b2Polygon polygon = b2Shape_GetPolygon(border_sensor_shape);
    const int vertexCount = polygon.count;
    const b2Vec2* vertices = polygon.vertices;

    // SDL2로 사각형 그리기
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  // 빨간색으로 설정

    for (int i = 0; i < vertexCount; ++i) {
        const int j = (i + 1) % vertexCount;
        SDL_RenderDrawLineF(
            renderer,
            x + vertices[i].x,
            y + vertices[i].y,
            x + vertices[j].x,
            y + vertices[j].y
        );
    }
}
#pragma endregion DebugDraw

void BorderTopSensorObject::OnDestroy()
{
    // 델리게이트 해제
    GameStage* game_stage = dynamic_cast<GameStage*>(GetCurrentStage());
    game_stage->GetBox2DManager().OnBeginSensorOverlap.Remove(begin_sensor_overlap_handle);
    game_stage->GetBox2DManager().OnEndSensorOverlap.Remove(end_sensor_overlap_handle);

    b2DestroyShape(border_sensor_shape);
    b2DestroyBody(border_sensor_body);

    border_sensor_shape = b2_nullShapeId;
    border_sensor_body = b2_nullBodyId;
}
