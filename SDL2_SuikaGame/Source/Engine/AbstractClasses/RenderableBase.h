#pragma once
#include "Engine/EngineTypes/RenderAnchor.h"
#include "Engine/EngineTypes/Vector2D.h"

// forward declaration
struct SDL_Renderer;
struct SDL_FRect;


class RenderableBase
{
public:
    virtual ~RenderableBase() = default;
    virtual void Render(
        SDL_Renderer* renderer,
        const Vector2D& position,
        RenderAnchor anchor = RenderAnchor::Center,
        float angle = 0.0f
    ) const = 0;

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
