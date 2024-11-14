#include "FruitObject.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"


FruitObject::FruitObject(GameEngine* engine)
    : GameObject(engine)
{
    z_order = 10;

    std::vector<FruitResourceObject*> fruit_resource;
    GetCurrentStage()->GetObjectManager().GetGameObjectsOfClass<FruitResourceObject>(fruit_resource);

    THROW_IF_FAILED(
        !fruit_resource.empty(),
        "Failed to find FruitResourceObject in the current stage"
    )

    // 체리, 딸기, 포도, 오렌지
    fruit_texture = fruit_resource.front()->GetRandomFruitTexture(0, 3);
}

void FruitObject::Update(float delta_time)
{
    fruit_position.Y += 300 * delta_time;
    if (fruit_position.Y > SCREEN_HEIGHT)
    {
        Destroy();
    }
}

void FruitObject::Render(SDL_Renderer* renderer) const
{
    fruit_texture->Render(renderer, fruit_position);
}
