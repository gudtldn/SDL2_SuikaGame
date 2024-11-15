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
        "Failed to load border texture! SDL Error: {}", SDL_GetError()
    )

    // Border 위치 설정
    border_texture = std::make_unique<Texture2D>(raw_border_texture);
}

void BorderObject::Update(float delta_time)
{
    // TODO: Implement Update
}

void BorderObject::Render(SDL_Renderer* renderer) const
{
    const Vector2D border_size = border_texture->GetSize();
    border_texture->Render(
        renderer,
        Vector2D(
            (SCREEN_WIDTH - border_size.X) / 2,
            (SCREEN_HEIGHT - border_size.Y) / 2
        )
    );
}
