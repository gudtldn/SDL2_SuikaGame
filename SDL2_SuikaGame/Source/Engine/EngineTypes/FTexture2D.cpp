#include "FTexture2D.h"


FTexture2D::FTexture2D(
    SDL_Texture* texture,
    const Vector2D& position
)
    : texture(texture, SDL_DestroyTexture)
    , tex_position(position)
{
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    tex_size = { static_cast<double>(w), static_cast<double>(h) };
}

FTexture2D::FTexture2D(
    SDL_Texture* texture,
    const Vector2D& position,
    const Vector2D& size
)
    : texture(texture, SDL_DestroyTexture)
    , tex_position(position)
    , tex_size(size)
{
}

void FTexture2D::Render(SDL_Renderer* renderer, const SDL_Rect* srcrect) const
{
    SDL_FRect dstrect = GetRect();
    SDL_RenderCopyF(renderer, texture.get(), srcrect, &dstrect);
}

SDL_FRect FTexture2D::GetRect() const
{
    return {
        .x = static_cast<float>(tex_position.X),
        .y = static_cast<float>(tex_position.Y),
        .w = static_cast<float>(tex_size.X),
        .h = static_cast<float>(tex_size.Y),
    };
}
