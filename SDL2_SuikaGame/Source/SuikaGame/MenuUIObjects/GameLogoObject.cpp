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
    );

    // 로고 위치 설정
    int logo_width, logo_height;
    SDL_QueryTexture(raw_logo_texture, nullptr, nullptr, &logo_width, &logo_height);

    logo_texture = std::make_unique<Texture2D>(
        raw_logo_texture,
        Vector2D(
            static_cast<float>((SCREEN_WIDTH - logo_width) / 2),
            static_cast<float>((SCREEN_HEIGHT - logo_height) / 2) * 0.4f
        ),
        Vector2D(
            static_cast<float>(logo_width),
            static_cast<float>(logo_height)
        )
    );
}

void GameLogoObject::Render(SDL_Renderer* renderer) const
{
    // 로고 렌더링
    logo_texture->Render(renderer);
}
