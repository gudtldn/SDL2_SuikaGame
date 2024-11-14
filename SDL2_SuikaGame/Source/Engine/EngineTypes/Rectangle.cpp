#include "Rectangle.h"


Rectangle::Rectangle()
    : color{ 255, 255, 255, 255 }
{
}

Rectangle::Rectangle(const Vector2D& size)
    : size(size)
    , color{ 255, 255, 255, 255 }
{
}

void Rectangle::Render(SDL_Renderer* renderer, const Vector2D& position) const
{
    const SDL_FRect rect = {
        .x = static_cast<float>(position.X),
        .y = static_cast<float>(position.Y),
        .w = static_cast<float>(size.X),
        .h = static_cast<float>(size.Y)
    };

    // 색상 설정
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // 사각형 그리기
    SDL_RenderFillRectF(renderer, &rect);

    // 색상 초기화
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
