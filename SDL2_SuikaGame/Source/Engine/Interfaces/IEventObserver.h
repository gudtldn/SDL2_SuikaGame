#pragma once
#include <SDL.h>


/// @brief Event Observer Interface
class IEventObserver
{
public:
    virtual ~IEventObserver() = default;

    /// @brief 이벤트 처리
    /// @param event SDL 이벤트
    virtual void OnEvent(const SDL_Event& event) = 0;
};
