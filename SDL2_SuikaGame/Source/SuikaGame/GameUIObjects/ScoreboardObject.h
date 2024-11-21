#pragma once
#include "EnginePCH.h"


/// @brief 점수를 표시하는 게임 오브젝트
class ScoreboardObject : public GameObject
{
private:
    /// @brief 스코어보드 배경 텍스처
    std::unique_ptr<Texture2D> bubble_texture;

    /// @brief "점수" 텍스쳐
    std::unique_ptr<Texture2D> text_texture;

    /// @brief 점수를 렌더링하는 객체
    std::unique_ptr<TextRender> score_text;

    /// @brief 스코어
    int score = 0;

    /// @brief 스코어 표시 위치
    Vector2D display_position;

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
