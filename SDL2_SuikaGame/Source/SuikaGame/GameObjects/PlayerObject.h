#pragma once
#include "EnginePCH.h"
#include <functional>

// delegate
struct FNextFruitDelegate
{
private:
    std::function<void(FruitObject*)> func;

public:
    FNextFruitDelegate() = default;
    ~FNextFruitDelegate() = default;

    void BindFunction(const std::function<void(FruitObject*)>& in_func)
    {
        if (func != nullptr)
        {
            throw std::runtime_error("FNextFruitDelegate::BindFunction already bound");
        }
        func = in_func;
    }

    void UnBind()
    {
        func = nullptr;
    }

    [[nodiscard]] bool IsBound() const
    {
        return func != nullptr;
    }

    void Execute(FruitObject* obj) const
    {
        if (IsBound())
        {
            func(obj);
        }
    }
};

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
    virtual void Update(float delta_time) override;
    virtual void Render(SDL_Renderer* renderer) const override;
    virtual void OnEvent(const SDL_Event& event) override;

private:
    /// @brief 플레이어 위치 설정
    /// @param new_x 새로운 x 위치
    inline void SetPlayerPosition(float new_x);
};
