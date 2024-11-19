#include "Renderable.h"
#include <SDL.h>


SDL_FRect Renderable::CalculateDestRect(
    const Vector2D& position,
    const Vector2D& size,
    RenderAnchor anchor
) const {
    SDL_FRect dest_rect = {
        .x = position.X,
        .y = position.Y,
        .w = size.X,
        .h = size.Y
    };

    // TODO: 나중에 비트 플래그로 수정
    switch (anchor)
    {
    case RenderAnchor::TopLeft:
        break;
    case RenderAnchor::TopCenter:
        dest_rect.x = position.X - size.X / 2;
        dest_rect.y = position.Y;
        break;
    case RenderAnchor::TopRight:
        dest_rect.x = position.X - size.X;
        dest_rect.y = position.Y;
        break;
    case RenderAnchor::CenterLeft:
        dest_rect.x = position.X;
        dest_rect.y = position.Y - size.Y / 2;
        break;
    case RenderAnchor::Center:
        dest_rect.x = position.X - size.X / 2;
        dest_rect.y = position.Y - size.Y / 2;
        break;
    case RenderAnchor::CenterRight:
        dest_rect.x = position.X - size.X;
        dest_rect.y = position.Y - size.Y / 2;
        break;
    case RenderAnchor::BottomLeft:
        dest_rect.x = position.X;
        dest_rect.y = position.Y - size.Y;
        break;
    case RenderAnchor::BottomCenter:
        dest_rect.x = position.X - size.X / 2;
        dest_rect.y = position.Y - size.Y;
        break;
    case RenderAnchor::BottomRight:
        dest_rect.x = position.X - size.X;
        dest_rect.y = position.Y - size.Y;
        break;
    }

    return dest_rect;
}
