#include "FruitObject.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"
#include <limits>


FruitObject::FruitObject(GameEngine* engine)
    : GameObject(engine)
    , fruit_texture(nullptr)
    , fruit_offset_position(std::numeric_limits<float>::infinity())
    , fruit_offset_size(std::numeric_limits<float>::infinity())
    , fruit_active(false)
    , is_init(false)
    , fruit_body()
    , fruit_shape()
{
    // 렌더링 순서
    z_order = 10;
}

void FruitObject::InitFruit(size_t idx)
{
    // fruit_texture 설정
    std::vector<FruitResourceObject*> fruit_resource;
    GetCurrentStage()->GetObjectManager().GetGameObjectsOfClass<FruitResourceObject>(fruit_resource);

    THROW_IF_FAILED(
        !fruit_resource.empty(),
        "Failed to find FruitResourceObject in the current stage"
    )
    const FruitResourceObject* fruit_resource_obj = fruit_resource.front();

    // 체리, 딸기, 포도, 오렌지
    fruit_resource_obj->GetFruit(
        idx,
        fruit_texture,
        fruit_offset_position,
        fruit_offset_size
    );

    // Box2D Body 초기화
    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.linearDamping = 0.0f;
    body_def.angularDamping = 0.1f;

    fruit_body = b2CreateBody(
        GetEngine()->GetBox2DManager().GetWorldID(),
        &body_def
    );
    b2Body_SetUserData(fruit_body, this);

    // 초기에는 비활성화
    b2Body_Disable(fruit_body);
    fruit_active = false;

    const b2Circle circle = {
        .center = {
            .x = fruit_position.X + fruit_offset_position.X,
            .y = fruit_position.Y + fruit_offset_position.Y,
        },
        .radius = fruit_texture->GetSize().Y / 2 + fruit_offset_size
    };

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.friction = 0.3f;

    fruit_shape = b2CreateCircleShape(fruit_body, &shape_def, &circle);

    // 초기화 성공
    is_init = true;
}

void FruitObject::InitRandomFruit()
{
    InitFruit(Math::RandRange(0, 4));
}

void FruitObject::BeginPlay()
{
    THROW_IF_FAILED(
        is_init,
        "FruitObject is not initialized please call InitFruit or InitRandomFruit"
    )

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

void FruitObject::OnDestroy()
{
    b2DestroyShape(fruit_shape);
    b2DestroyBody(fruit_body);
    
    fruit_shape = b2_nullShapeId;
    fruit_body = b2_nullBodyId;
}
