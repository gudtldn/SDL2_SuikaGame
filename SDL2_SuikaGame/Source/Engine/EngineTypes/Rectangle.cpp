#include "Rectangle.h"

#ifdef _DEBUG
#include "Engine/Utils/Math.h"
#endif


Rectangle::Rectangle()
    : color{ 255, 255, 255, 255 }
{
}

Rectangle::Rectangle(const Vector2D& size)
    : size(size)
    , color{ 255, 255, 255, 255 }
{
}

void Rectangle::Render(SDL_Renderer* renderer, const Vector2D& position, RenderAnchor anchor, float angle) const
{
#ifdef _DEBUG
    if (!Math::IsNearlyZero(angle))
    {
        throw std::runtime_error("Rectangle::Render: angle is not supported!");
    }
#endif

    const SDL_FRect dst_rect = CalculateDestRect(position, size, anchor);

    // 색상 설정
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // 사각형 그리기
    SDL_RenderFillRectF(renderer, &dst_rect);

    // 색상 초기화
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
