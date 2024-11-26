#pragma once
#include "Engine/EngineTypes/RenderAnchor.h"
#include "Engine/EngineTypes/Vector2D.h"
#include <SDL_blendmode.h>
#include <SDL_render.h>
#include <SDL_rect.h>


class RenderableBase
{
protected:
    /// @brief 블렌딩 모드
    SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE;

public:
    virtual ~RenderableBase() = default;
    virtual void Render(
        SDL_Renderer* renderer,
        const Vector2D& position,
        RenderAnchor anchor = RenderAnchor::Center,
        float angle = 0.0f
    ) const = 0;

    /// @brief 블렌딩 모드를 설정합니다.
    /// @param new_blend_mode 새로운 블렌딩 모드
    void SetBlendMode(SDL_BlendMode new_blend_mode) { blend_mode = new_blend_mode; }

    /// @brief 블렌딩 모드를 가져옵니다.
    /// @return 블렌딩 모드
    [[nodiscard]] SDL_BlendMode GetBlendMode() const { return blend_mode; }

protected:
    /// @brief 위치와 크기를 받아, anchor에 따른 실제 렌더링 위치를 계산합니다.
    /// @param position 위치
    /// @param size 크기
    /// @param anchor 앵커
    /// @return 계산된 렌더링 위치
    [[nodiscard]] virtual SDL_FRect CalculateDestRect(
        const Vector2D& position,
        const Vector2D& size,
        RenderAnchor anchor
    ) const;
};
