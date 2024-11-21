#include "ScoreboardObject.h"


ScoreboardObject::ScoreboardObject(GameEngine* engine)
    : GameObject(engine)
    , display_position{
        SCREEN_WIDTH / 2 * 0.3f,
        SCREEN_HEIGHT / 2 * 0.5f
    }
{
    // z-order 설정
    z_order = 1;

    // 스코어보드 배경 텍스처 로드
    SDL_Texture* raw_bubble_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/bubble.png");
    THROW_IF_FAILED(
        raw_bubble_texture,
        "Failed to load bubble texture! SDL Error: {}", SDL_GetError()
    )

    SDL_Texture* raw_text_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/score_text.png");
    THROW_IF_FAILED(
        raw_text_texture,
        "Failed to load text texture! SDL Error: {}", SDL_GetError()
    )

    // Border 배경 위치 설정
    bubble_texture = std::make_unique<Texture2D>(raw_bubble_texture);

    // "점수" 텍스처 로딩
    text_texture = std::make_unique<Texture2D>(raw_text_texture);

    // 폰트 로딩
    score_text = std::make_unique<TextRender>("./Contents/Fonts/Hakgyoansim Dunggeunmiso TTF R.ttf", 48);
    score_text->SetText("0");
}

void ScoreboardObject::Render(SDL_Renderer* renderer) const
{
    bubble_texture->Render(renderer, display_position);
    text_texture->Render(
        renderer,
        {
            display_position.X,
            display_position.Y - 122.5f
        }
    );
    score_text->Render(
        renderer,
        {
            display_position.X,
            display_position.Y - 40.0f
        }
    );
}
