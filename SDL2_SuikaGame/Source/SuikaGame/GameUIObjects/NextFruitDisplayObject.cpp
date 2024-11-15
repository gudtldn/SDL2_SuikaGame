#include "NextFruitDisplayObject.h"
#include "SuikaGame/GameObjects/PlayerObject.h"
#include "SuikaGame/GameObjects/FruitObject.h"


NextFruitDisplayObject::NextFruitDisplayObject(GameEngine* engine)
    : GameObject(engine)
    , bubble_position({
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

    int w, h;
    SDL_QueryTexture(raw_bubble_texture, nullptr, nullptr, &w, &h);

    bubble_texture = std::make_unique<Texture2D>(
        raw_bubble_texture,
        Vector2D(
            static_cast<float>(w) * 0.75f,
            static_cast<float>(h) * 0.75f
        )
    );
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
        fruit->SetFruitPosition(bubble_position);
    });
}

void NextFruitDisplayObject::Render(SDL_Renderer* renderer) const
{
    const Vector2D bubble_size = bubble_texture->GetSize();
    bubble_texture->Render(
        renderer,
        bubble_position - bubble_size / 2.0f
    );
}
