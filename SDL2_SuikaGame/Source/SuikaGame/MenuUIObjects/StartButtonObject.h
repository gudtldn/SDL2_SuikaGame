#pragma once
#include "EnginePCH.h"


/// @brief 시작 버튼 오브젝트
class StartButtonObject : public GameObject
{
private:
    // 버튼 컴포넌트
    std::unique_ptr<TextureButtonComponent> start_button;

    // 버튼 원래 위치
    Vector2D button_origin;

    // 현재 버튼 위치
    Vector2D current_button_position;

    // 버튼 애니메이션 상수
    static constexpr float BUTTON_OSCILLATION_SPEED = 3.0f; // 버튼 움직임의 속도 (주기)
    static constexpr float BUTTON_OSCILLATION_RANGE = 8.0f; // 버튼 움직임의 범위 (진폭)

public:
    StartButtonObject(GameEngine* engine);

protected:
    // 게임 오브젝트가 생성된 직후에 호출됩니다.
    virtual void BeginPlay() override;

    // 매 프레임마다 호출됩니다.
    virtual void Update(float delta_time) override;

    // 게임 오브젝트가 렌더링될 때 호출됩니다.
    virtual void Render(SDL_Renderer* renderer) const override;

    // SDL 이벤트 발생 시 호출됩니다.
    virtual void OnEvent(const SDL_Event& event) override;
};
