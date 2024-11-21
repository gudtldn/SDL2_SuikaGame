#include "NextFruitDisplayObject.h"
#include "SuikaGame/GameObjects/PlayerObject.h"
#include "SuikaGame/GameObjects/FruitObject.h"


NextFruitDisplayObject::NextFruitDisplayObject(GameEngine* engine)
    : GameObject(engine)
    , display_position({
        SCREEN_WIDTH * 0.85f,
        SCREEN_HEIGHT * 0.25f
    })
    , display_fruit_texture(nullptr)
{
    SDL_Texture* raw_bubble_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/bubble.png");
    THROW_IF_FAILED(
        raw_bubble_texture,
        "Failed to load bubble texture! SDL Error: {}", SDL_GetError()
    )

    SDL_Texture* raw_text_texture = IMG_LoadTexture(engine->GetRenderer(), "Contents/Textures/next_text.png");
    THROW_IF_FAILED(
        raw_text_texture,
        "Failed to load text texture! SDL Error: {}", SDL_GetError()
    )

    int w, h;
    SDL_QueryTexture(raw_bubble_texture, nullptr, nullptr, &w, &h);

    bubble_texture = std::make_unique<Texture2D>(
        raw_bubble_texture,
        Vector2D(
            static_cast<float>(w) * 0.75f,
            static_cast<float>(h) * 0.75f
        )
    );
    text_texture = std::make_unique<Texture2D>(raw_text_texture);
}

void NextFruitDisplayObject::BeginPlay()
{
    std::vector<PlayerObject*> players;
    GetCurrentStage()->GetObjectManager().GetGameObjectsOfClass<PlayerObject>(players);
    THROW_IF_FAILED(
        !players.empty(),
        "Failed to get players of NextFruitDisplayObject!"
    )

    PlayerObject* player = players.front();
    player->next_fruit_delegate.BindFunction([this](FruitObject* fruit)
    {
        fruit->SetFruitPosition(display_position);
    });
}

void NextFruitDisplayObject::Render(SDL_Renderer* renderer) const
{
    bubble_texture->Render(renderer, display_position);
    text_texture->Render(
        renderer,
        {
            display_position.X,
            display_position.Y - 95.0f
        }
    );
}
