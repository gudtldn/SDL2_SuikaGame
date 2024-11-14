#include "ScoreboardObject.h"


ScoreboardObject::ScoreboardObject(GameEngine* engine)
    : GameObject(engine)
    , bubble_texture(nullptr)
    , score(0)
{
    // z-order 설정
    z_order = 1;

    // 스코어보드 배경 텍스처 로드
    SDL_Texture* raw_bubble_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/bubble.png");
    THROW_IF_FAILED(
        raw_bubble_texture,
        "Failed to load bubble texture! SDL Error: {}", SDL_GetError()
    )

    // Border 배경 위치 설정
    bubble_texture = std::make_unique<Texture2D>(raw_bubble_texture);
}

void ScoreboardObject::Update(float delta_time)
{
    // LOG_INFO("Score: {}", score);
}

void ScoreboardObject::Render(SDL_Renderer* renderer) const
{
    const Vector2D bubble_pos = bubble_texture->GetSize();
    bubble_texture->Render(
        renderer,
        // FIXME: 값 비율이 뭔가 이상한거 같음
        Vector2D(
            (SCREEN_WIDTH - bubble_pos.X) * 0.075f,
            (SCREEN_HEIGHT - bubble_pos.Y) * 0.1f
        )
    );
}
