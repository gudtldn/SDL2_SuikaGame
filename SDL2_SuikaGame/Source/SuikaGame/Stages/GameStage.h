#pragma once
#include "EnginePCH.h"


/// @brief 게임 스테이지
class GameStage : public Stage
{
private:
    /// @brief 물리 엔진 관리자
    Box2DManager box2d_manager;

public:
    GameStage(GameEngine* engine);

    /// @brief 물리 엔진 관리자를 가져옵니다.
    Box2DManager& GetBox2DManager() { return box2d_manager; }

protected:
    virtual void InitializeObjects() override;
    virtual void HandleFixedUpdate(float fixed_time) override;
};
