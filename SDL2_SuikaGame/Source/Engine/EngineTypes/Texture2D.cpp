#include "Texture2D.h"


Texture2D::Texture2D(SDL_Texture* texture)
    : texture(texture, SDL_DestroyTexture)
{
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    tex_size = { static_cast<float>(w), static_cast<float>(h) };
}

Texture2D::Texture2D(
    SDL_Texture* texture,
    const Vector2D& size
)
    : texture(texture, SDL_DestroyTexture)
    , tex_size(size)
{
}

void Texture2D::Render(SDL_Renderer* renderer, const Vector2D& position, RenderAnchor anchor, float angle) const
{
    const auto [cal_x, cal_y, cal_w, cal_h] = CalculateDestRect(position, tex_size, anchor);
    const SDL_Rect dst_rect = {
        .x = static_cast<int>(cal_x),
        .y = static_cast<int>(cal_y),
        .w = static_cast<int>(cal_w),
        .h = static_cast<int>(cal_h),
    };
    SDL_RenderCopyEx(
        renderer,
        texture.get(),
        nullptr,
        &dst_rect,
        angle,
        nullptr,
        SDL_FLIP_NONE
    );
}
