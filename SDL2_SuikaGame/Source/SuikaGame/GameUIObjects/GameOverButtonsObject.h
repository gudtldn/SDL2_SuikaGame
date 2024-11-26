#pragma once
#include "EnginePCH.h"


/// @brief 게임 오버 상태에서 사용자가 게임을 재시작하거나 메인 메뉴로 돌아갈 수 있는 버튼을 제공하는 오브젝트입니다.
class GameOverButtonsObject : public GameObject
{
    /// @brief 게임 재시작 버튼
    std::unique_ptr<TextureButtonComponent> restart_button;

    /// @brief 메인 메뉴로 돌아가는 버튼
    std::unique_ptr<TextureButtonComponent> title_button;


    /// @brief 게임 재시작 버튼의 위치
    Vector2D restart_button_position;

    /// @brief 메인 메뉴로 돌아가는 버튼의 위치
    Vector2D title_button_position;

public:
    GameOverButtonsObject(GameEngine* engine);

protected:
    virtual void OnEvent(const SDL_Event& event) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
