#ifdef _DEBUG // 디버그 모드에서만 컴파일합니다.

#include "DebugDrawObject.h"
#include "SuikaGame/GameObjects/FruitObject.h"
#include "SuikaGame/GameObjects/BorderTopSensorObject.h"


DebugDrawObject::DebugDrawObject(GameEngine* engine)
    : GameObject(engine)
{
    z_order = 999;
}

void DebugDrawObject::OnEvent(const SDL_Event& event)
{
    if (
        event.type == SDL_KEYDOWN
        && event.key.keysym.sym == SDLK_BACKQUOTE
    ) {
        toggle_debug = !toggle_debug;
    }
}

void DebugDrawObject::Render(SDL_Renderer* renderer) const
{
    if (!toggle_debug) return;

#pragma region Draw Fruit Info
{
    std::vector<FruitObject*> fruits;
    GetCurrentStage()->GetObjectManager()
        .GetGameObjectsOfClass<FruitObject>(fruits);

    for (const auto fruit : fruits)
    {
        // ReSharper disable once StringLiteralTypo
        TextRender shape_index_text { "./Contents/Fonts/Jalnan2TTF.ttf", 24 };
        shape_index_text.SetText(std::to_string(fruit->GetFruitShape().index1));
        shape_index_text.SetColor({ 0, 255, 255, 255 });
        shape_index_text.Render(renderer, fruit->GetFruitPosition());

        const auto [lower_bound, upper_bound] = b2Shape_GetAABB(fruit->GetFruitShape());
        const SDL_Rect rect = {
            .x = static_cast<int>(lower_bound.x),
            .y = static_cast<int>(lower_bound.y),
            .w = static_cast<int>((upper_bound.x - lower_bound.x)),
            .h = static_cast<int>((upper_bound.y - lower_bound.y))
        };

        // AABB 그리기
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 빨간색
        SDL_RenderDrawRect(renderer, &rect);
    }
}
#pragma endregion Draw Fruit Info

#pragma region Draw Sensor Info
{
    std::vector<BorderTopSensorObject*> sensors;
    GetCurrentStage()->GetObjectManager()
        .GetGameObjectsOfClass<BorderTopSensorObject>(sensors);

    for (const auto sensor : sensors)
    {
        {
            // b2PolygonShape에서 정점 정보 가져오기
            auto [x, y] = b2Body_GetPosition(sensor->GetSensorBody());
            const b2Polygon polygon = b2Shape_GetPolygon(sensor->GetSensorShape());
            const int vertexCount = polygon.count;
            const b2Vec2* vertices = polygon.vertices;

            // SDL2로 사각형 그리기
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  // 빨간색으로 설정

            for (int i = 0; i < vertexCount; ++i) {
                const int j = (i + 1) % vertexCount;
                SDL_RenderDrawLineF(
                    renderer,
                    x + vertices[i].x,
                    y + vertices[i].y,
                    x + vertices[j].x,
                    y + vertices[j].y
                );
            }
        }
        {
            const auto [lower_bound, upper_bound] = b2Shape_GetAABB(sensor->GetSensorShape());
            const SDL_Rect rect = {
                .x = static_cast<int>(lower_bound.x),
                .y = static_cast<int>(lower_bound.y),
                .w = static_cast<int>((upper_bound.x - lower_bound.x)),
                .h = static_cast<int>((upper_bound.y - lower_bound.y))
            };

            // AABB 그리기
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 빨간색
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
#pragma endregion Draw Sensor Info
}

#endif // _DEBUG
