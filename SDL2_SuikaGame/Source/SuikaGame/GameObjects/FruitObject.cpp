#include "FruitObject.h"
#include "SuikaGame/GameResources/FruitResourceObject.h"


FruitObject::FruitObject(GameEngine* engine)
    : GameObject(engine)
{
    std::vector<FruitResourceObject*> fruit_resource;
    GetCurrentStage()->GetObjectManager().GetGameObjectsOfClass<FruitResourceObject>(fruit_resource);

    THROW_IF_FAILED(
        !fruit_resource.empty(),
        "Failed to find FruitResourceObject in the current stage"
    )

    fruit_resource_object = fruit_resource.front();
}

void FruitObject::BeginPlay()
{
    // 체리, 딸기, 포도, 오렌지
    fruit_texture = fruit_resource_object->GetRandomFruitTexture(0, 3);
}

void FruitObject::Update(float delta_time)
{
}

void FruitObject::Render(SDL_Renderer* renderer) const
{
}
