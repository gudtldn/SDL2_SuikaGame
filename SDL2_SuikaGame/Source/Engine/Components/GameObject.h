#pragma once
#include <cstdint>

/// @brief 게임 오브젝트 클래스
class GameObject
{
protected:
    /// @brief 게임 오브젝트의 z-order
    int32_t z_order = 0;

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    // 생성이 되었을 때 호출됩니다.
    virtual void BeginPlay() {};

    // 매 프레임마다 호출됩니다.
    virtual void Update(double delta_time) {};

    // 게임 오브젝트가 렌더링될 때 호출됩니다.
    virtual void Render() {};


    /****** Getter & Setter ******/

    /// @brief z-order를 가져옵니다.
    int32_t GetZOrder() const { return z_order; }
};
