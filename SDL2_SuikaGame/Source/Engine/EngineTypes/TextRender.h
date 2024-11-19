#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Engine/AbstractClasses/Renderable.h"


class TextRender : public Renderable
{
    /// @brief 텍스트 렌더링에 사용할 텍스처
    mutable std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> cached_texture;

    /// @brief 캐시를 다시 불러올지 여부
    mutable bool reload_cache;

    /// @brief 텍스트 렌더링에 사용할 폰트
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;

    /// @brief 텍스트 색상
    SDL_Color color;

    /// @brief 폰트 크기
    int font_size;

    /// @brief 텍스트
    std::string text;

public:
    TextRender(const char* font_path, int font_size);

    [[nodiscard]] int GetFontSize() const { return font_size; }
    void SetFontSize(int new_font_size) { font_size = new_font_size; }

    [[nodiscard]] SDL_Color GetColor() const { return color; }
    void SetColor(SDL_Color new_color) { color = new_color; }

    [[nodiscard]] const std::string& GetText() const { return text; }
    void SetText(const std::string& new_text)
    {
        text = new_text;
        reload_cache = true;
    }
    void SetText(std::string&& new_text)
    {
        text = std::move(new_text);
        reload_cache = true;
    }

    virtual void Render(
        SDL_Renderer* renderer,
        const Vector2D& position,
        RenderAnchor anchor = RenderAnchor::Center,
        float angle = 0.0f
    ) const override;

private:
    inline void ConvertTextToTexture(SDL_Renderer* renderer) const;
};
