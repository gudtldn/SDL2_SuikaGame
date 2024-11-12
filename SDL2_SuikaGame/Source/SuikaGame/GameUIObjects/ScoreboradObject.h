#pragma once
#include "EnginePCH.h"


/// @brief 점수를 표시하는 게임 오브젝트
class ScoreboradObject : public GameObject
{
private:
    /// @brief 스코어보드 배경 텍스처
    std::unique_ptr<FTexture2D> bubble_texture;

    /// @brief 스코어
    int score = 0;

public:
    ScoreboradObject(GameEngine* engine);


    /****** Getter && Setter ******/

    /// @brief 스코어를 가져옵니다.
    inline int GetScore() const { return score; }

    /// @brief 스코어를 증가시킵니다.
    inline void AddScore(int value) { score += value; }

protected:
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};
