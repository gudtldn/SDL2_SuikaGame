#pragma once
#include "EnginePCH.h"


/// @brief 게임 스테이지
class GameStage : public Stage
{
private:
    /// @brief 물리 엔진 관리자
    Box2DManager box2d_manager;

    /// @brief 게임 오버 여부
    bool is_game_over;

public:
    GameStage(GameEngine* engine);

    /// @brief 물리 엔진 관리자를 가져옵니다.
    Box2DManager& GetBox2DManager() { return box2d_manager; }

    /// @brief 게임 오버 여부를 반환합니다.
    [[nodiscard]] bool IsGameOver() const { return is_game_over; }

    /// @brief 게임 오버 여부를 설정합니다.
    void SetGameOver(bool new_game_over) { is_game_over = new_game_over; }

protected:
    virtual void InitializeObjects() override;
    virtual void HandleUpdate(float delta_time) override;
    virtual void HandleFixedUpdate(float fixed_time) override;
};
