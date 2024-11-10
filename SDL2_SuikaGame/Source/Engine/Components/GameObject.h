#pragma once
#include <memory>
#include <cstdint>

// forward declaration
class Stage;
class GameEngine;
struct SDL_Renderer;


/// @brief 게임 오브젝트 클래스
class GameObject
{
private:
    /// @brief 게임 엔진
    GameEngine* engine;


protected:
    /// @brief 게임 오브젝트의 z-order
    int32_t z_order = 0;


public:
    GameObject(GameEngine* engine)
        : engine(engine) {}

    virtual ~GameObject() = default;

    // 생성이 되었을 때 호출됩니다.
    virtual void BeginPlay();

    // 매 프레임마다 호출됩니다.
    virtual void Update(double delta_time);

    // 게임 오브젝트가 렌더링될 때 호출됩니다.
    virtual void Render(SDL_Renderer* renderer);

    // 게임 오브젝트가 파괴될 때 호출됩니다.
    virtual void OnDestory(); // TODO: 아무데서도 호출되지 않음


    /****** Getter & Setter ******/

    /// @brief z-order를 가져옵니다.
    int32_t GetZOrder() const { return z_order; }

    /// @brief z-order를 설정합니다.
    void SetZOrder(int32_t z_order) { this->z_order = z_order; }

    /// @brief 게임 엔진을 가져옵니다.
    GameEngine* GetEngine() const { return engine; }

    /// @brief 현재 스테이지를 가져옵니다.
    inline Stage* GetCurrentStage() const;
};
