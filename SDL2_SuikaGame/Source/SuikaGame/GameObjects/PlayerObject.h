#pragma once
#include "EnginePCH.h"


/// @brief 플레이어 오브젝트
class PlayerObject : public GameObject
{
private:
    /// @brief 플레이어
    Rectangle player;

    /// @brief 가이드 선
    Rectangle guide_line;

private:
    // 가이드 선 크기
    static constexpr float GUIDE_LINE_WIDTH = 3.0;
    static constexpr float GUIDE_LINE_HEIGHT = 585.0;

    // Player line
    static constexpr float PLAYER_LINE_WIDTH = 448.0;

    // Player
    static constexpr float PLAYER_SIZE = 48;
    static constexpr float PLAYER_SPEED = 600;

    float min_player_x;
    float max_player_x;
    float player_line_y;

public:
    PlayerObject(GameEngine* engine);

protected:
    virtual void BeginPlay() override;
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
    virtual void OnEvent(const SDL_Event& event) override;

private:
    /// @brief 플레이어 위치 설정
    /// @param new_x 새로운 x 위치
    inline void SetPlayerPosition(float new_x);
};
