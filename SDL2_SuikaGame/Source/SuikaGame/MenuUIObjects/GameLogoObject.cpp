#include "GameLogoObject.h"


GameLogoObject::GameLogoObject(GameEngine* engine)
    : GameObject(engine)
    , logo_texture(nullptr)
{
    // 로고 텍스처 로드
    SDL_Texture* raw_logo_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/suika_game_logo.png");
    THROW_IF_FAILED(
        raw_logo_texture,
        "Failed to load logo texture! SDL Error: {}", SDL_GetError()
    )

    // 로고 위치 설정
    logo_texture = std::make_unique<Texture2D>(raw_logo_texture);
}

void GameLogoObject::Render(SDL_Renderer* renderer) const
{
    // 로고 렌더링
    const Vector2D logo_size = logo_texture->GetSize();
    logo_texture->Render(
        renderer,
        Vector2D(
            (SCREEN_WIDTH - logo_size.X) / 2,
            (SCREEN_HEIGHT - logo_size.Y) / 2 * 0.4f
        )
    );
}
