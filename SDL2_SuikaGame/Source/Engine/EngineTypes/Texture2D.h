#pragma once
#include "Engine/EngineTypes/Vector2D.h"

#include <SDL.h>
#include <memory>


/// @brief SDL_Texture Wrapper 클래스
class Texture2D {
private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
    Vector2D tex_position;
    Vector2D tex_size;

public:
    Texture2D(SDL_Texture* texture, const Vector2D& position);
    Texture2D(SDL_Texture* texture, const Vector2D& position, const Vector2D& size);
    ~Texture2D() = default;

    // 복사 & 대입 연산자 삭제
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&&) noexcept = default;
    Texture2D& operator=(Texture2D&&) noexcept = default;

    /// @brief 텍스처를 렌더링합니다.
    /// @param renderer 렌더러
    /// @param srcrect 렌더링할 영역 (nullptr일 경우 전체 영역)
    void Render(SDL_Renderer* renderer, const SDL_Rect* srcrect = nullptr) const;


    /****** Getter & Setter ******/

    /// @brief 텍스처를 가져옵니다.
    /// @return SDL_Texture* 텍스처
    SDL_Texture* GetTexture() const { return texture.get(); }

    /// @brief 텍스처의 Rect를 가져옵니다.
    /// @return SDL_Rect 텍스처의 Rect
    SDL_Rect GetRect() const;

    /// @brief 텍스처의 위치를 가져옵니다.
    /// @return Vector2D 텍스처의 위치
    Vector2D GetPosition() const { return this->tex_position; }

    /// @brief 텍스처의 위치를 설정합니다.
    void SetPosition(const Vector2D& position) { this->tex_position = position; }

    /// @brief 텍스처의 크기를 가져옵니다.
    /// @return Vector2D 텍스처의 크기
    Vector2D GetSize() const { return this->tex_size; }

    /// @brief 텍스처의 크기를 설정합니다.
    void SetSize(const Vector2D& size) { this->tex_size = size; }
};
