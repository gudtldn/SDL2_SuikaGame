#pragma once
#include "EnginePCH.h"


/// @brief 점수를 표시하는 오브젝트입니다.
class GameOverScoreboardObject : public GameObject
{
    /// @brief 점수를 표시하는 텍스트 렌더링 컴포넌트입니다.
    std::unique_ptr<TextRender> score_text;

public:
    GameOverScoreboardObject(GameEngine *engine);

protected:
    virtual void BeginPlay() override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
