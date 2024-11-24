#include "FruitObject.h"
#include "SuikaGame/Stages/GameStage.h"
#include "SuikaGame/GameResources/FruitResource.h"
#include "SuikaGame/GameResources/ScoreResource.h"
#include "SuikaGame/GameObjects/BorderBottomCollisionObject.h"
#include "SuikaGame/GameObjects/BorderTopSensorObject.h"
#include <limits>


FruitObject::FruitObject(GameEngine* engine)
    : GameObject(engine)
    , fruit_texture(nullptr)
    , fruit_idx(std::numeric_limits<size_t>::max())
    , fruit_offset_position(std::numeric_limits<float>::infinity())
    , fruit_offset_size(std::numeric_limits<float>::infinity())
    , merge_sound(nullptr)
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
    const FruitResource* fruit_resource_obj =
        GetEngine()->GetResourceManager().GetResource<FruitResource>();

    // 체리, 딸기, 포도, 오렌지
    fruit_idx = idx;
    fruit_resource_obj->GetFruit(
        idx,
        fruit_texture,
        fruit_offset_position,
        fruit_offset_size
    );

    merge_sound = fruit_resource_obj->GetFruitMergeSound();

    // Box2D Body 초기화
    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.linearDamping = 0.0f;
    body_def.angularDamping = 0.1f;
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
    shape_def.friction = 0.15f;
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
        if (
            !GetFruitActive() // 과일이 비활성화 되어있거나
            || !IsValid()     // 자신이 유효하지 않거나
            || b != this      // 자신하고 발생한 이벤트가 아닐 경우
        ) return;             // 무시하고 리턴

        // BorderBottomCollisionObject와 충돌했을 경우
        if (dynamic_cast<BorderBottomCollisionObject*>(a) && !is_first_landed)
        {
            is_first_landed = true;
            bool _ = OnLandedBottomCollision.ExecuteIfBound();
        }

        // FruitObject와 충돌했을 경우
        else if (FruitObject* other_fruit_obj = dynamic_cast<FruitObject*>(a))
        {
            if (!is_first_landed)
            {
                is_first_landed = true;
                bool _ = OnLandedBottomCollision.ExecuteIfBound();
                CheckFruitCollisionWithBorderSensor();
            }
            else if (!other_fruit_obj->is_first_landed)
            {
                other_fruit_obj->is_first_landed = true;
                bool _ = other_fruit_obj->OnLandedBottomCollision.ExecuteIfBound();
                CheckFruitCollisionWithBorderSensor();
            }

            // 같은 과일일 경우
            if (fruit_idx == other_fruit_obj->fruit_idx)
            {
                if (fruit_idx < FruitResource::FRUIT_COUNT-1)
                {
                    FruitObject* new_fruit = game_stage->GetObjectManager().CreateGameObject<FruitObject>();
                    new_fruit->InitFruit(fruit_idx + 1);
                    new_fruit->SetFruitPosition(
                        (fruit_position + other_fruit_obj->GetFruitPosition()) / 2.0f
                    );
                    new_fruit->SetFruitActive(true);
                }

                // pop사운드 재생
                Mix_PlayChannel(0, merge_sound, 0);

                // 점수 증가
                ScoreResource* score_resource = GetEngine()->GetResourceManager().GetResource<ScoreResource>();

                const int temp_idx = static_cast<int>(fruit_idx) + 1;
                score_resource->AddScore(temp_idx * (temp_idx + 1) / 2);

                // 과일 물리엔진 비활성화
                b2Body_Disable(other_fruit_obj->fruit_body);
                b2Body_Disable(fruit_body);
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
            bool _ = OnLandedBottomCollision.ExecuteIfBound();
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
        bool _ = OnLandedBottomCollision.ExecuteIfBound();
    }

    if (b2Shape_IsValid(fruit_shape))
    {
        b2DestroyShape(fruit_shape);
    }
    if (b2Body_IsValid(fruit_body))
    {
        b2DestroyBody(fruit_body);
    }
    
    fruit_shape = b2_nullShapeId;
    fruit_body = b2_nullBodyId;
}

void FruitObject::CheckFruitCollisionWithBorderSensor() const
{
    BorderTopSensorObject* border_sensor;
    {
        std::vector<BorderTopSensorObject*> borders;
        GetCurrentStage()->GetObjectManager().GetGameObjectsOfClass(borders);
        THROW_IF_FAILED(
            !borders.empty(),
            "Failed to get borders for fruit object"
        )
        border_sensor = borders.front();
    }

    const b2AABB sensor_aabb = b2Shape_GetAABB(border_sensor->GetSensorShape());
    const b2AABB self_aabb = b2Shape_GetAABB(fruit_shape);

    // 과일이 센서에 닿았는지 AABB로 확인
    if (
        sensor_aabb.lowerBound.x <= self_aabb.upperBound.x && self_aabb.lowerBound.x <= sensor_aabb.upperBound.x
        && sensor_aabb.lowerBound.y <= self_aabb.upperBound.y && self_aabb.lowerBound.y <= sensor_aabb.upperBound.y
    ) {
        dynamic_cast<GameStage*>(GetCurrentStage())->SetGameOver(true);
    }
}
