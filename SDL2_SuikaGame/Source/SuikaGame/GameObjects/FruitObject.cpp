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

    const FruitResourceObject* fruit_resource_obj = fruit_resource.front();

    // 체리, 딸기, 포도, 오렌지
    const int rand_idx = Math::RandRange(0, 4);
    fruit_texture = fruit_resource_obj->GetFruitTexture(rand_idx);
    fruit_offset_position = fruit_resource_obj->GetFruitOffsetPosition(rand_idx);
    fruit_offset_size = fruit_resource_obj->GetFruitOffsetSize(rand_idx);
}

void FruitObject::Update(float delta_time)
{
    if (!fruit_active) return;

    fruit_position.Y += 300 * delta_time;
    if (fruit_position.Y > SCREEN_HEIGHT)
    {
        Destroy();
    }
}

void FruitObject::Render(SDL_Renderer* renderer) const
{
    fruit_texture->Render(
        renderer,
        fruit_position - fruit_texture->GetSize() / 2
    );


    // 과일 텍스쳐의 중심에 원을 그립니다. // TODO: 테스트
    const int32_t radius = fruit_texture->GetSize().Y / 2 + fruit_offset_size;
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        const float pos_x = fruit_position.X + fruit_offset_position.X;
        const float_t pos_y = fruit_position.Y + fruit_offset_position.Y;
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, pos_x + x, pos_y - y);
        SDL_RenderDrawPoint(renderer, pos_x + x, pos_y + y);
        SDL_RenderDrawPoint(renderer, pos_x - x, pos_y - y);
        SDL_RenderDrawPoint(renderer, pos_x - x, pos_y + y);
        SDL_RenderDrawPoint(renderer, pos_x + y, pos_y - x);
        SDL_RenderDrawPoint(renderer, pos_x + y, pos_y + x);
        SDL_RenderDrawPoint(renderer, pos_x - y, pos_y - x);
        SDL_RenderDrawPoint(renderer, pos_x - y, pos_y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
