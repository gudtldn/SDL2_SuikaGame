#pragma once
#include "Engine/EngineTypes/Vector2D.h"
#include <SDL.h>


/// @brief 기본 사각형 클래스
class Rectangle
{
private:
    /// @brief 크기
    Vector2D size;

    /// @brief 색상
    SDL_Color color;

public:
    Rectangle();
    Rectangle(const Vector2D& size);
    ~Rectangle() = default;

    void Render(SDL_Renderer* renderer, const Vector2D& position) const;


    // Getter & Setter

    /// @brief 크기를 반환합니다.
    [[nodiscard]] Vector2D GetSize() const { return size; }

    /// @brief 크기를 설정합니다.
    void SetSize(const Vector2D& new_size) { size = new_size; }

    /// @brief 색상을 반환합니다.
    [[nodiscard]] SDL_Color GetColor() const { return color; }

    /// @brief 색상을 설정합니다.
    void SetColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A) { color = { .r= R, .g= G, .b= B, .a= A}; }
};
