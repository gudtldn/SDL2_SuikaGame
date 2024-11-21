#include "TextRender.h"
#include "Engine/Utils/LogMacros.h"


TextRender::TextRender(const char* font_path, int font_size)
    : cached_texture(nullptr, SDL_DestroyTexture)
    , reload_cache(false)
    , font(nullptr, TTF_CloseFont)
    , color({.r = 0x00, .g = 0x00, .b = 0x00, .a = 0x00})
    , font_size(font_size)
{
    TTF_Font* raw_font = TTF_OpenFont(font_path, font_size);
    if (!raw_font)
    {
        LOG_ERROR(
            "Failed to open font: '{}'\n{}",
            font_path, TTF_GetError()
        );
        throw std::runtime_error(
            std::format("Failed to open font: '{}'", font_path)
        );
    }
    font.reset(raw_font);
}

void TextRender::Render(SDL_Renderer* renderer, const Vector2D& position, RenderAnchor anchor, float angle) const
{
    if (reload_cache)
    {
        ConvertTextToTexture(renderer);
        reload_cache = false;
    }

    int width, height;
    SDL_QueryTexture(cached_texture.get(), nullptr, nullptr, &width, &height);

    const SDL_FRect dest_rect = CalculateDestRect(
        position,
        {
            static_cast<float>(width),
            static_cast<float>(height)
        },
        anchor
    );

    SDL_RenderCopyExF(
        renderer,
        cached_texture.get(),
        nullptr,
        &dest_rect,
        angle,
        nullptr,
        SDL_FLIP_NONE
    );
}

inline void TextRender::ConvertTextToTexture(SDL_Renderer* renderer) const
{
    // 텍스트 렌더링
    SDL_Surface* surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);

    if (!surface)
    {
        // 오류 처리
        LOG_ERROR(
            "Failed to render text: '{}'\n{}",
            text, TTF_GetError()
        );
        throw std::runtime_error(
            std::format("Failed to render text: '{}'", text)
        );
    }

    cached_texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
    SDL_FreeSurface(surface);
}
