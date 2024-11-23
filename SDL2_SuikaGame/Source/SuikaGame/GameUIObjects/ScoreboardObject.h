#pragma once
#include "EnginePCH.h"


/// @brief 점수를 표시하는 게임 오브젝트
class ScoreboardObject : public GameObject
{
private:
    /// @brief 스코어보드 배경 텍스처
    std::unique_ptr<Texture2D> bubble_texture;

    /// @brief "점수" 텍스쳐
    std::unique_ptr<Texture2D> score_label_texture;

    /// @brief 점수를 렌더링하는 객체
    std::unique_ptr<TextRender> score_text;

    /// @brief "BEST SCORE"를 렌더링 하는 객체
    std::unique_ptr<TextRender> high_score_label;

    /// @brief 최고점수를 렌더링하는 객체
    std::unique_ptr<TextRender> high_score_text;

    /// @brief 스코어 표시 위치
    Vector2D display_position;

    /// @brief 원래 위치
    Vector2D origin;

    /// @brief 애니메이션에 사용될 랜덤 오프셋
    float random_offset;

public:
    ScoreboardObject(GameEngine* engine);

protected:
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
