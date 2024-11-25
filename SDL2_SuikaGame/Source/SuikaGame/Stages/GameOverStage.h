#pragma once
#include "EnginePCH.h"


/// @brief 게임오버 스테이지
class GameOverStage : public Stage
{
public:
    GameOverStage(GameEngine* engine)
        : Stage(engine) {}

protected:
    virtual void InitializeStage() override;
};
