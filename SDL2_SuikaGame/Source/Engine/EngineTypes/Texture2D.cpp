#include "Texture2D.h"


Texture2D::Texture2D(
    SDL_Texture* texture,
    const Vector2D& position
)
    : texture(texture, SDL_DestroyTexture)
    , tex_position(position)
{
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    tex_size = { static_cast<float>(w), static_cast<float>(h) };
}

Texture2D::Texture2D(
    SDL_Texture* texture,
    const Vector2D& position,
    const Vector2D& size
)
    : texture(texture, SDL_DestroyTexture)
    , tex_position(position)
    , tex_size(size)
{
}

void Texture2D::Render(SDL_Renderer* renderer, const SDL_Rect* srcrect) const
{
    SDL_Rect dstrect = GetRect();
    SDL_RenderCopy(renderer, texture.get(), srcrect, &dstrect);
}

SDL_Rect Texture2D::GetRect() const
{
    return {
        .x = static_cast<int>(tex_position.X),
        .y = static_cast<int>(tex_position.Y),
        .w = static_cast<int>(tex_size.X),
        .h = static_cast<int>(tex_size.Y),
    };
}
