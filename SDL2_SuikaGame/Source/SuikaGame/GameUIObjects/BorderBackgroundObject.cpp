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
        "Failed to load border background texture! SDL Error: %s", SDL_GetError()
    );

    // Border 배경 위치 설정
    int border_bg_width, border_bg_height;
    SDL_QueryTexture(raw_border_background_texture, NULL, NULL, &border_bg_width, &border_bg_height);

    border_background_texture = std::make_unique<Texture2D>(
        raw_border_background_texture,
        Vector2D(
            static_cast<float>((SCREEN_WIDTH - border_bg_width) / 2),
            static_cast<float>((SCREEN_HEIGHT - border_bg_height) / 2)
        ),
        Vector2D(
            static_cast<float>(border_bg_width),
            static_cast<float>(border_bg_height)
        )
    );
}

void BorderBackgroundObject::Render(SDL_Renderer* renderer) const
{
    // Border 배경 렌더링
    border_background_texture->Render(renderer);
}
