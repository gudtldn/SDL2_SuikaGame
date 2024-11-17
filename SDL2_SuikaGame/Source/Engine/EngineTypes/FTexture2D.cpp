#include "FTexture2D.h"


FTexture2D::FTexture2D(SDL_Texture* texture)
    : texture(texture, SDL_DestroyTexture)
{
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    tex_size = { static_cast<float>(w), static_cast<float>(h) };
}

FTexture2D::FTexture2D(
    SDL_Texture* texture,
    const Vector2D& size
)
    : texture(texture, SDL_DestroyTexture)
    , tex_size(size)
{
}

void FTexture2D::Render(SDL_Renderer* renderer, const Vector2D& position, float angle) const
{
    SDL_FRect dstrect = {
        .x = static_cast<float>(position.X),
        .y = static_cast<float>(position.Y),
        .w = static_cast<float>(tex_size.X),
        .h = static_cast<float>(tex_size.Y),
    };
    SDL_RenderCopyExF(renderer, texture.get(), nullptr, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}
