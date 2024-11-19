#pragma once
#include "EnginePCH.h"


/// @brief 점수를 표시하는 게임 오브젝트
class ScoreboardObject : public GameObject
{
private:
    /// @brief 스코어보드 배경 텍스처
    std::unique_ptr<Texture2D> bubble_texture;

    std::unique_ptr<TextRender> score_text;

    /// @brief 스코어
    int score = 0;

public:
    ScoreboardObject(GameEngine* engine);


    /****** Getter && Setter ******/

    /// @brief 스코어를 가져옵니다.
    int GetScore() const { return score; }

    /// @brief 스코어를 증가시킵니다.
    void AddScore(int value)
    {
        score += value;
        score_text->SetText(std::to_string(score));
    }

protected:
    virtual void Render(SDL_Renderer* renderer) const override;
};
