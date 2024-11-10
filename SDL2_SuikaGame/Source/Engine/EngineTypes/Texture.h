#pragma once
#include <SDL.h>
#include <memory>

/// @brief SDL_Texture Wrapper 클래스
class Texture {
private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
    SDL_Rect rect;

public:
    Texture(SDL_Texture* texture, const SDL_Rect& rect);
    ~Texture() = default;

    // 복사 & 대입 연산자 삭제
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&) noexcept = default;
    Texture& operator=(Texture&&) noexcept = default;

    /// @brief 텍스처를 반환합니다.
    /// @return SDL_Texture* 텍스처
    SDL_Texture* GetTexture() const { return texture.get(); }

    /// @brief 텍스처의 Rect를 반환합니다.
    /// @return SDL_Rect 텍스처의 Rect
    const SDL_Rect& GetRect() const { return rect; }

    /// @brief 텍스처를 렌더링합니다.
    void Render(SDL_Renderer* renderer, const SDL_Rect* srcrect = nullptr) const;

    /// @brief 텍스처의 Rect를 설정합니다.
    void SetRect(const SDL_Rect& rect) { this->rect = rect; }
};
