#include "Texture.h"


Texture::Texture(SDL_Texture* texture, const SDL_Rect& rect)
    : texture(texture, SDL_DestroyTexture)
    , rect(rect)
{
}

void Texture::Render(SDL_Renderer* renderer, const SDL_Rect* srcrect) const
{
    SDL_RenderCopy(renderer, texture.get(), srcrect, &rect);
}