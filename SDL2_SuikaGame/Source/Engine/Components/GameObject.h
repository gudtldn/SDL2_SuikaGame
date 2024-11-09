#pragma once


/// @brief 게임 오브젝트 클래스
class GameObject
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    // 생성이 되었을 때 호출됩니다.
    virtual void BeginPlay() {};

    // 매 프레임마다 호출됩니다.
    virtual void Update(double delta_time) {};

    // 게임 오브젝트가 렌더링될 때 호출됩니다.
    virtual void Render() {};
};
