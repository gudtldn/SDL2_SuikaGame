#pragma once
#ifdef _DEBUG // 디버그 모드에서만 컴파일합니다.

#include "EnginePCH.h"


/// @brief 오브젝트의 디버깅 정보를 그리는 오브젝트입니다.
class DebugDrawObject : public GameObject
{
    /// @brief 디버깅 정보를 표시할지 여부를 나타냅니다.
    bool toggle_debug = false;

public:
    DebugDrawObject(GameEngine* engine);

    virtual void OnEvent(const SDL_Event& event) override;
    virtual void Render(SDL_Renderer* renderer) const override;
};

#endif // _DEBUG
