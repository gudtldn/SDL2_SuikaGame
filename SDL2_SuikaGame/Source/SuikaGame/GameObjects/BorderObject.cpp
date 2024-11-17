#include "BorderObject.h"
#include "SuikaGame/Stages/GameStage.h"
#include "SuikaGame/GameObjects/BorderBottomCollisionObject.h"
#include <ranges>



BorderObject::BorderObject(GameEngine* engine)
    : GameObject(engine)
    , border_texture(nullptr)
{
    // 렌더링 순서 (가장 앞에 렌더링)
    z_order = 100;

    // Border 텍스처 로드
    SDL_Texture* raw_border_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/border.png");
    THROW_IF_FAILED(
        raw_border_texture,
        "Failed to load border texture! SDL Error: {}", SDL_GetError()
    )

    int w, h;
    SDL_QueryTexture(raw_border_texture, nullptr, nullptr, &w, &h);

    // Border 위치 설정
    border_texture = std::make_unique<Texture2D>(
        raw_border_texture,
        Vector2D(
            static_cast<float>(w),
            static_cast<float>(h)
        )
    );
    texture_position = Vector2D(
        SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2
    );


    // Box2D Body 초기화
    constexpr SDL_FRect body_rect[] = {
        { // Left
            .x = -6.0f - 224.0f,
            .y = -280.0f,
            .w = 8.0f,
            .h = 560.0f
        },
        { // Right
            .x = 6.0f + 224.0f,
            .y = -280.0f,
            .w = 8.0f,
            .h = 560.0f
        }
        // Bottom은 BorderBottomCollisionObject에 구현
    };

    for (const auto [idx, rect] : body_rect | std::views::enumerate)
    {
        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.type = b2_staticBody;
        body_def.position = {
            .x = texture_position.X + rect.x,
            .y = texture_position.Y + rect.y
        };
        bodies[idx] = b2CreateBody(
            dynamic_cast<GameStage*>(GetCurrentStage())->GetBox2DManager().GetWorldID(),
            &body_def
        );
        b2Body_SetUserData(bodies[idx], this);

        b2Polygon border_polygon = b2MakeBox(rect.w, rect.h);
        b2ShapeDef border_shape_def = b2DefaultShapeDef();
        border_shape_def.enableContactEvents = false;
        border_shape_def.enableHitEvents = false;
        shapes[idx] = b2CreatePolygonShape(bodies[idx], &border_shape_def, &border_polygon);
    }
}

void BorderObject::BeginPlay()
{
    // BorderObject의 Bottom 부분 CollisionObject
    GetCurrentStage()->GetObjectManager().CreateGameObject<BorderBottomCollisionObject>();
}

void BorderObject::Render(SDL_Renderer* renderer) const
{
    const Vector2D border_size = border_texture->GetSize();
    border_texture->Render(
        renderer,
        texture_position - border_size / 2
    );
}

void BorderObject::OnDestroy()
{
    for (const auto [idx, body] : bodies | std::views::enumerate)
    {
        b2DestroyShape(shapes[idx]);
        b2DestroyBody(body);

        shapes[idx] = b2_nullShapeId;
        body = b2_nullBodyId;
    }
}
