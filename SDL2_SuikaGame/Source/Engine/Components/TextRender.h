#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Engine/AbstractClasses/Renderable.h"


/// @brief 텍스트 렌더링을 담당하는 클래스
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

    /// @brief 폰트 크기를 반환합니다.
    /// @return 폰트 크기
    [[nodiscard]] int GetFontSize() const { return font_size; }

    /// @brief 폰트 크기를 설정합니다.
    /// @param new_font_size 새로운 폰트 크기
    void SetFontSize(int new_font_size) { font_size = new_font_size; }

    /// @brief 텍스트 색상을 반환합니다.
    /// @return 텍스트 색상
    [[nodiscard]] SDL_Color GetColor() const { return color; }

    /// @brief 텍스트 색상을 설정합니다.
    /// @param new_color 새로운 텍스트 색상
    void SetColor(SDL_Color new_color) { color = new_color; }

    /// @brief 텍스트를 반환합니다.
    /// @return 텍스트
    [[nodiscard]] const std::string& GetText() const { return text; }

    /// @brief 텍스트를 설정합니다.
    /// @param new_text 새로운 텍스트
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

    /// @brief 텍스트를 렌더링합니다.
    /// @param renderer 렌더러
    /// @param position 위치
    /// @param anchor 앵커
    /// @param angle 각도
    virtual void Render(
        SDL_Renderer* renderer,
        const Vector2D& position,
        RenderAnchor anchor = RenderAnchor::Center,
        float angle = 0.0f
    ) const override;

protected:
    /// @brief 텍스트를 텍스처로 변환합니다.
    /// @param renderer 렌더러
    inline void ConvertTextToTexture(SDL_Renderer* renderer) const;
};
