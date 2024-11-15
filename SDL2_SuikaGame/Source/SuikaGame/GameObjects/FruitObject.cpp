#include "FruitObject.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"


FruitObject::FruitObject(GameEngine* engine)
    : GameObject(engine)
{
    // 렌더링 순서
    z_order = 10;

    // fruit_texture 설정
    std::vector<FruitResourceObject*> fruit_resource;
    GetCurrentStage()->GetObjectManager().GetGameObjectsOfClass<FruitResourceObject>(fruit_resource);

    THROW_IF_FAILED(
        !fruit_resource.empty(),
        "Failed to find FruitResourceObject in the current stage"
    )

    const FruitResourceObject* fruit_resource_obj = fruit_resource.front();

    // 체리, 딸기, 포도, 오렌지
    const int rand_idx = Math::RandRange(0, 4);
    fruit_texture = fruit_resource_obj->GetFruitTexture(rand_idx);
    fruit_offset_position = fruit_resource_obj->GetFruitOffsetPosition(rand_idx);
    fruit_offset_size = fruit_resource_obj->GetFruitOffsetSize(rand_idx);

    // Box2D Body 초기화
    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    fruit_body = b2CreateBody(
        engine->GetBox2DManager().GetWorldID(),
        &body_def
    );
    SetFruitActive(false);

    b2Circle circle = {
        .center = {
            .x = fruit_position.X + fruit_offset_position.X,
            .y = fruit_position.Y + fruit_offset_position.Y,
        },
        .radius = fruit_texture->GetSize().Y / 2 + fruit_offset_size
    };

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.friction = 0.3f;

    b2CreateCircleShape(
        fruit_body,
        &shape_def,
        &circle
    );
}

void FruitObject::Update(float delta_time)
{
    const auto [x, y] = b2Body_GetPosition(fruit_body);
    fruit_position.X = x;
    fruit_position.Y = y;

    if (fruit_position.Y > SCREEN_HEIGHT)
    {
        Destroy();
    }
}

void FruitObject::Render(SDL_Renderer* renderer) const
{
    fruit_texture->Render(
        renderer,
        fruit_position - fruit_texture->GetSize() / 2
    );
}
