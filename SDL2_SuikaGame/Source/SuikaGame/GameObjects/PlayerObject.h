#pragma once
#include "EnginePCH.h"
#include <functional>

// forward declaration
class FruitObject;

// delegate
DECLARE_DELEGATE_OneParam(FNextFruitDelegate, FruitObject*);


/// @brief 플레이어 오브젝트
class PlayerObject : public GameObject
{
private:
    /// @brief 플레이어 텍스처
    std::unique_ptr<Texture2D> player_texture;

    /// @brief 플레이어 가이드 선
    Rectangle player_guide_line;

    /// @brief 플레이어 위치
    Vector2D player_position;


    /// @brief 현재 과일
    FruitObject* current_fruit;

    /// @brief 다음 과일
    FruitObject* next_fruit;

private:
    // Guideline
    static constexpr float GUIDE_LINE_WIDTH = 3.0f;
    static constexpr float GUIDE_LINE_HEIGHT = 625.0f;

    // Border
    static constexpr float BORDER_WIDTH = 448.0f;
    static constexpr float BORDER_MARGIN = 25.0f;

    // Player
    static constexpr float PLAYER_WIDTH = 104.0f;
    static constexpr float PLAYER_HEIGHT = 64.0f;
    static constexpr float PLAYER_SPEED = 600.0f;

    float min_border_x;
    float max_border_x;

public:
    FNextFruitDelegate next_fruit_delegate;

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

    /// @brief 다음 과일 설정
    void SetNextFruit();
};
