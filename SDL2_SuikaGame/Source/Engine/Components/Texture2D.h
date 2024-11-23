#pragma once
#include "Engine/EngineTypes/Vector2D.h"
#include "Engine/AbstractClasses/RenderableBase.h"

#include <SDL.h>
#include <memory>


/// @brief SDL_Texture Wrapper 클래스
class Texture2D : public RenderableBase
{
private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
    Vector2D tex_size;

public:
    Texture2D(SDL_Texture* texture);
    Texture2D(SDL_Texture* texture, const Vector2D& size);

    // 복사 & 대입 연산자 삭제
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&&) noexcept = default;
    Texture2D& operator=(Texture2D&&) noexcept = default;

    /// @brief 텍스처를 렌더링합니다.
    /// @param renderer 렌더러
    /// @param position 위치
    /// @param angle 각도
    /// @param anchor 앵커
    virtual void Render(
        SDL_Renderer* renderer,
        const Vector2D& position,
        RenderAnchor anchor = RenderAnchor::Center,
        float angle = 0.0f
    ) const override;

    /****** Getter & Setter ******/

    /// @brief 텍스처를 가져옵니다.
    /// @return SDL_Texture* 텍스처
    [[nodiscard]] SDL_Texture* GetTexture() const { return texture.get(); }

    /// @brief 텍스처의 크기를 가져옵니다.
    /// @return Vector2D 텍스처의 크기
    [[nodiscard]] Vector2D GetSize() const { return tex_size; }

    /// @brief 텍스처의 크기를 설정합니다.
    void SetSize(const Vector2D& size) { tex_size = size; }
};
