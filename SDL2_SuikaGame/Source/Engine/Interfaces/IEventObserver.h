#pragma once
#include <SDL.h>


/// @brief Event Observer Interface
/// @details 이벤트 처리를 위한 Observer 인터페이스
class IEventObserver
{
public:
    virtual ~IEventObserver() = default;

    /// @brief 이벤트 처리
    /// @param event SDL 이벤트
    virtual void OnEvent(const SDL_Event& event) = 0;
};
