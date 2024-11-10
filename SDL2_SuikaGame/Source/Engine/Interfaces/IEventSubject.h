#pragma once
#include <memory>
#include <SDL.h>

// forward declaration
class IEventObserver;


/// @brief Event Subject Interface
/// @details 이벤트 처리를 위한 Subject 인터페이스
class IEventSubject
{
public:
    virtual ~IEventSubject() = default;

    // 이벤트 옵저버 추가
    virtual void AddObserver(std::shared_ptr<IEventObserver> observer) = 0;

    // 이벤트 옵저버 제거
    virtual void RemoveObserver(std::shared_ptr<IEventObserver> observer) = 0;

    // 이벤트 알림
    virtual void NotifyObservers(const SDL_Event& event) = 0;
};