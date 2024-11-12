#pragma once
#include "Engine/EngineTypes/Vector2D.h"
#include <SDL.h>


/// @brief 기본 사각형 클래스
class Rectangle
{
private:
    /// @brief 위치
    Vector2D position;

    /// @brief 크기
    Vector2D size;

    /// @brief 색상
    SDL_Color color;

public:
    Rectangle();
    Rectangle(const Vector2D& position, const Vector2D& size);
    ~Rectangle() = default;

    void Render(SDL_Renderer* renderer) const;


    // Getter & Setter

    /// @brief 위치를 반환합니다.
    inline Vector2D GetPosition() const { return position; }

    /// @brief 위치를 설정합니다.
    inline void SetPosition(const Vector2D& new_position) { position = new_position; }

    /// @brief 크기를 반환합니다.
    inline Vector2D GetSize() const { return size; }

    /// @brief 크기를 설정합니다.
    inline void SetSize(const Vector2D& new_size) { size = new_size; }

    /// @brief 색상을 반환합니다.
    inline SDL_Color GetColor() const { return color; }

    /// @brief 색상을 설정합니다.
    inline void SetColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A) { color = { R, G, B, A }; }
};
