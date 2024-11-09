#pragma once
#include <memory>
#include <SDL.h>

// forward declaration
class IEventObserver;


/// @brief Event Subject Interface
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