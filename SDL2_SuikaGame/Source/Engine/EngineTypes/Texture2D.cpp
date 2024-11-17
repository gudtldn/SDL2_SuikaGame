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

void Texture2D::Render(SDL_Renderer* renderer, const Vector2D& position, float angle) const

{
    const SDL_Rect dstrect = {
        .x = static_cast<int>(position.X),
        .y = static_cast<int>(position.Y),
        .w = static_cast<int>(tex_size.X),
        .h = static_cast<int>(tex_size.Y),
    };
    SDL_RenderCopyEx(renderer, texture.get(), nullptr, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}
