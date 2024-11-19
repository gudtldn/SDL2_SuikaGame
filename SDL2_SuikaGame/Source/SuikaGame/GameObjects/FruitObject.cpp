#include "FruitObject.h"
#include "SuikaGame/Stages/GameStage.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"
#include "SuikaGame/GameObjects/BorderBottomCollisionObject.h"
#include <limits>


FruitObject::FruitObject(GameEngine* engine)
    : GameObject(engine)
    , fruit_texture(nullptr)
    , fruit_idx(std::numeric_limits<size_t>::max())
    , fruit_offset_position(std::numeric_limits<float>::infinity())
    , fruit_offset_size(std::numeric_limits<float>::infinity())
    , fruit_active(false)
    , is_first_landed(false)
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
    fruit_idx = idx;
    fruit_resource_obj->GetFruit(
        idx,
        fruit_texture,
        fruit_offset_position,
        fruit_offset_size
    );

    // Box2D Body 초기화
    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.linearDamping = 0.1f;
    body_def.angularDamping = 0.2f;
    body_def.userData = this;

    fruit_body = b2CreateBody(
        dynamic_cast<GameStage*>(GetCurrentStage())->GetBox2DManager().GetWorldID(),
        &body_def
    );

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
    shape_def.userData = this;

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

    // Delegate Bind
    GameStage* game_stage = dynamic_cast<GameStage*>(GetCurrentStage());
    on_begin_overlap_handle = game_stage->GetBox2DManager()
        .OnBeginOverlap.AddFunction([this, game_stage](GameObject* a, const GameObject* b)
    {
        // 과일이 비활성화 되어있거나, 자신하고 발생한 이벤트가 아닐 경우 리턴
        if (!GetFruitActive() || b != this) return;

        // BorderBottomCollisionObject와 충돌했을 경우
        if (dynamic_cast<BorderBottomCollisionObject*>(a) && !is_first_landed)
        {
            is_first_landed = true;
            OnLandedBottomCollision.Execute();
        }

        // FruitObject와 충돌했을 경우
        else if (FruitObject* other_fruit_obj = dynamic_cast<FruitObject*>(a))
        {
            if (!is_first_landed)
            {
                is_first_landed = true;
                OnLandedBottomCollision.Execute();
            }
            else if (!other_fruit_obj->is_first_landed)
            {
                other_fruit_obj->is_first_landed = true;
                other_fruit_obj->OnLandedBottomCollision.Execute();
            }

            // 같은 과일일 경우
            if (fruit_idx == other_fruit_obj->fruit_idx)
            {
                if (fruit_idx < FruitResourceObject::FRUIT_COUNT)
                {
                    FruitObject* new_fruit = game_stage->GetObjectManager().CreateGameObject<FruitObject>();
                    new_fruit->InitFruit(fruit_idx + 1);
                    new_fruit->SetFruitPosition(
                        (fruit_position + other_fruit_obj->GetFruitPosition()) / 2.0f
                    );
                    new_fruit->is_first_landed = true;
                    new_fruit->SetFruitActive(true);

                    // TODO: 합쳐지는 효과음 재생
                }
                other_fruit_obj->Destroy();
                Destroy();
            }
        }
    });
}

void FruitObject::Update(float delta_time)
{
    const auto [x, y] = b2Body_GetPosition(fruit_body);
    fruit_position.X = x;
    fruit_position.Y = y;

    if (fruit_position.Y > SCREEN_HEIGHT)
    {
        if (!is_first_landed)
        {
            is_first_landed = true;
            OnLandedBottomCollision.Execute();
        }
        Destroy();
    }
}

void FruitObject::Render(SDL_Renderer* renderer) const
{
    const auto [cos, sin] = b2Body_GetRotation(fruit_body);
    fruit_texture->Render(
        renderer,
        fruit_position,
        RenderAnchor::Center,
        Math::RadianToDegree(Math::Atan2(sin, cos))
    );
}

void FruitObject::OnDestroy()
{
    dynamic_cast<GameStage*>(GetCurrentStage())->GetBox2DManager()
        .OnBeginOverlap.Remove(on_begin_overlap_handle);

    if (!is_first_landed)
    {
        OnLandedBottomCollision.Execute();
    }

    b2DestroyShape(fruit_shape);
    b2DestroyBody(fruit_body);
    
    fruit_shape = b2_nullShapeId;
    fruit_body = b2_nullBodyId;
}
