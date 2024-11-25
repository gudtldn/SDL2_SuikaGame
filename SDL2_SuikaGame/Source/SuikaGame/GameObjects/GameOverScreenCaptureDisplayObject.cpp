#include "GameOverScreenCaptureDisplayObject.h"
#include "SuikaGame/GameResources/TempScreenCaptureResource.h"


GameOverScreenCaptureDisplayObject::GameOverScreenCaptureDisplayObject(GameEngine* engine)
    : GameObject(engine)
    , game_over_captured_texture(nullptr)
{
    // z-order 설정
    z_order = 1;
}

void GameOverScreenCaptureDisplayObject::BeginPlay()
{
    game_over_captured_texture = GetEngine()->GetResourceManager()
        .GetResource<TempScreenCaptureResource>()->MoveTexture();

    game_over_captured_texture->SetSize({
        SCREEN_WIDTH * 0.49f,
        SCREEN_HEIGHT * 0.49f
    });
}

void GameOverScreenCaptureDisplayObject::Render(SDL_Renderer* renderer) const
{
    if (game_over_captured_texture)
    {
        game_over_captured_texture->Render(
            renderer,
            {
                92.0f,
                (SCREEN_HEIGHT / 2.0f) + 26.0f
            },
            RenderAnchor::CenterLeft
        );
    }
}
