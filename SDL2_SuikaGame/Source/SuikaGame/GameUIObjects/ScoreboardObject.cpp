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
    );

    // Border 배경 위치 설정
    int bubble_width, bubble_height;
    SDL_QueryTexture(raw_bubble_texture, nullptr, nullptr, &bubble_width, &bubble_height);

    bubble_texture = std::make_unique<Texture2D>(
        raw_bubble_texture,
        Vector2D(
            static_cast<float>((SCREEN_WIDTH - bubble_width) * 0.075f),
            static_cast<float>((SCREEN_HEIGHT - bubble_height) * 0.1f)
        ),
        Vector2D(
            static_cast<float>(bubble_width),
            static_cast<float>(bubble_height)
        )
    );
}

void ScoreboardObject::Update(float delta_time)
{
    // LOG_INFO("Score: {}", score);
}

void ScoreboardObject::Render(SDL_Renderer* renderer) const
{
    bubble_texture->Render(renderer);
}
