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
    static constexpr double GUIDE_LINE_WIDTH = 4.0;
    static constexpr double GUIDE_LINE_HEIGHT = 585.0;

    // Player line
    static constexpr double PLAYER_LINE_WIDTH = 448.0;

    // Player
    static constexpr double PLAYER_SIZE = 48;
    static constexpr double PLAYER_SPEED = 600;

    double min_player_x;
    double max_player_x;
    double player_line_y;

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
    inline void SetPlayerPosition(double new_x);
};
