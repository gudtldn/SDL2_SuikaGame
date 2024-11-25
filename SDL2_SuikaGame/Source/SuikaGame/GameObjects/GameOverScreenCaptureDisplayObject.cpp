#include "GameOverScreenCaptureDisplayObject.h"
#include "SuikaGame/GameResources/TempScreenCaptureResource.h"


GameOverScreenCaptureDisplayObject::GameOverScreenCaptureDisplayObject(GameEngine* engine)
    : GameObject(engine)
    , game_over_texture(nullptr)
{
}

void GameOverScreenCaptureDisplayObject::BeginPlay()
{
    game_over_texture = GetEngine()->GetResourceManager()
        .GetResource<TempScreenCaptureResource>()->MoveTexture();

    game_over_texture->SetSize({
        SCREEN_WIDTH / 1.5f,
        SCREEN_HEIGHT / 1.5f
    });
}

void GameOverScreenCaptureDisplayObject::Render(SDL_Renderer* renderer) const
{
    if (game_over_texture)
    {
        game_over_texture->Render(
            renderer,
            {
                100.0f,
                SCREEN_HEIGHT / 2.0f
            },
            RenderAnchor::CenterLeft
        );
    }
}
