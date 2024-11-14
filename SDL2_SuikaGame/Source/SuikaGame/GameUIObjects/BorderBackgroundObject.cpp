#include "BorderBackgroundObject.h"


BorderBackgroundObject::BorderBackgroundObject(GameEngine* engine)
    : GameObject(engine)
    , border_background_texture(nullptr)
{
    // 렌더링 순서
    z_order = -99;

    // Border 배경 텍스처 로드
    SDL_Texture* raw_border_background_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/border_bg.png");
    THROW_IF_FAILED(
        raw_border_background_texture,
        "Failed to load border background texture! SDL Error: {}", SDL_GetError()
    )

    // Border 배경 위치 설정
    border_background_texture = std::make_unique<Texture2D>(raw_border_background_texture);
}

void BorderBackgroundObject::Render(SDL_Renderer* renderer) const
{
    // Border 배경 렌더링
    const Vector2D border_bg_size = border_background_texture->GetSize();
    border_background_texture->Render(
        renderer,
        Vector2D(
            (SCREEN_WIDTH - border_bg_size.X) / 2,
            (SCREEN_HEIGHT - border_bg_size.Y) / 2
        )
    );
}
