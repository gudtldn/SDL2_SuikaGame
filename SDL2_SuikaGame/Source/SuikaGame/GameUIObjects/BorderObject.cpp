#include "BorderObject.h"


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
        "Failed to load border texture! SDL Error: %s", SDL_GetError()
    );

    // Border 위치 설정
    int border_width, border_height;
    SDL_QueryTexture(raw_border_texture, NULL, NULL, &border_width, &border_height);

    border_texture = std::make_unique<Texture2D>(
        raw_border_texture,
        Vector2D(
            static_cast<float>((SCREEN_WIDTH - border_width) / 2),
            static_cast<float>((SCREEN_HEIGHT - border_height) / 2)
        ),
        Vector2D(
            static_cast<float>(border_width),
            static_cast<float>(border_height)
        )
    );
}

void BorderObject::Update(float delta_time)
{
    // TODO: Implement Update
}

void BorderObject::Render(SDL_Renderer* renderer) const
{
    border_texture->Render(renderer);
}
