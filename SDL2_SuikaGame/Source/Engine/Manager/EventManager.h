#pragma once
#include "Interfaces/IEventSubject.h"

#include <vector>
#include <memory>

class EventManager : public IEventSubject
{
private:
    /// @brief 옵저버 목록
    std::vector<std::shared_ptr<IEventObserver>> observers;

public:
    /// @brief 옵저버 추가
    /// @param observer 옵저버
    void AddObserver(std::shared_ptr<IEventObserver> observer) override;

    /// @brief 옵저버 제거
    /// @param observer 옵저버
    void RemoveObserver(std::shared_ptr<IEventObserver> observer) override;

    /// @brief 옵저버에게 이벤트 알림
    /// @param event SDL 이벤트
    void NotifyObservers(const SDL_Event& event) override;
};
