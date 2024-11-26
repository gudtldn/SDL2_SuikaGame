#pragma once
#include "Engine/AbstractClasses/RenderableBase.h"
#include <SDL.h>
#include <functional>

// forward declaration
class Texture2D;


/// @brief 텍스처 버튼 컴포넌트
class TextureButtonComponent : public RenderableBase
{
    std::unique_ptr<Texture2D> texture;

private:
    bool is_hovered = false;
    bool is_pressed = false;

private:
    // 콜백 함수들
    std::function<void()> on_hover_callback;         // 마우스가 버튼 위에 올라갔을 때
    std::function<void()> on_unhover_callback;       // 마우스가 버튼에서 벗어났을 때
    std::function<void()> on_click_callback;         // 마우스가 버튼을 클릭했을 때
    std::function<void()> on_release_callback;       // 마우스가 버튼에서 뗐을 때
    std::function<void()> on_hover_clicked_callback; // 마우스가 버튼하고 상호작용을 완료했을 때

public:
    explicit TextureButtonComponent(Texture2D* texture);
    explicit TextureButtonComponent(std::unique_ptr<Texture2D> texture);

    void HandleEvents(const SDL_Event& event, const Vector2D& position);
    virtual void Render(
        SDL_Renderer* renderer,
        const Vector2D& position,
        RenderAnchor anchor = RenderAnchor::Center,
        float angle = 0.0f
    ) const override;


    /****** Method ******/

    /// @brief 버튼을 호버한 것처럼 시뮬레이션합니다.
    void SimulateHover();

    /// @brief 버튼을 언호버한 것처럼 시뮬레이션합니다.
    void SimulateUnhover();

    /// @brief 버튼을 클릭한 것처럼 시뮬레이션합니다.
    void SimulateClick();

    /// @brief 버튼을 릴리즈한 것처럼 시뮬레이션합니다.
    void SimulateRelease();

    /// @brief 버튼을 클릭한 것처럼 시뮬레이션하고, 릴리즈한 것처럼 시뮬레이션합니다.
    void SimulateClickAndRelease();

    /// @brief 버튼을 호버한 상태에서 클릭한 것처럼 시뮬레이션합니다.
    void SimulateHoverClicked() const;


    /****** Getter && Setter ******/

    /// @brief 버튼이 호버 상태인지 확인합니다.
    /// @return 버튼이 호버 상태인지 여부
    [[nodiscard]] bool IsHovered() const { return is_hovered; }

    /// @brief 버튼이 눌린 상태인지 확인합니다.
    /// @return 버튼이 눌린 상태인지 여부
    [[nodiscard]] bool IsPressed() const { return is_pressed; }

    /// @brief 텍스처를 가져옵니다.
    /// @return 텍스처
    [[nodiscard]] Texture2D* GetTexture() const { return texture.get(); }

    /// @brief 텍스처를 설정합니다.
    /// @param new_texture 새로운 텍스처
    void SetTexture(Texture2D* new_texture) { texture.reset(new_texture); }
    void SetTexture(std::unique_ptr<Texture2D> new_texture) { texture = std::move(new_texture); }


    /****** SetCallback ******/

    /// @brief 마우스가 버튼 위에 올라갔을 때 호출되는 콜백 함수를 설정합니다.
    /// @param callback 호출할 콜백 함수
    void SetOnHoverCallback(const std::function<void()>& callback) { on_hover_callback = callback; }

    /// @brief 마우스가 버튼에서 벗어났을 때 호출되는 콜백 함수를 설정합니다.
    /// @param callback 호출할 콜백 함수
    void SetOnUnhoverCallback(const std::function<void()>& callback) { on_unhover_callback = callback; }

    /// @brief 마우스가 버튼을 클릭했을 때 호출되는 콜백 함수를 설정합니다.
    /// @param callback 호출할 콜백 함수
    void SetOnClickCallback(const std::function<void()>& callback) { on_click_callback = callback; }

    /// @brief 마우스가 버튼에서 뗐을 때 호출되는 콜백 함수를 설정합니다.
    /// @param callback 호출할 콜백 함수
    void SetOnReleaseCallback(const std::function<void()>& callback) { on_release_callback = callback; }

    /// @brief 마우스가 버튼하고 상호작용을 완료했을 때 호출되는 콜백 함수를 설정합니다.
    /// @param callback 호출할 콜백 함수
    void SetOnHoverClickedCallback(const std::function<void()>& callback) { on_hover_clicked_callback = callback; }
};
