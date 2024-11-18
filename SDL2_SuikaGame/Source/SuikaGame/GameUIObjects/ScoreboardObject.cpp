#include "ScoreboardObject.h"


ScoreboardObject::ScoreboardObject(GameEngine* engine)
    : GameObject(engine)
    , bubble_texture(nullptr)
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
    bubble_texture->Render(
        renderer,
        Vector2D(
            SCREEN_WIDTH / 2 * 0.3f,
            SCREEN_HEIGHT / 2 * 0.5f
        )
    );
}
