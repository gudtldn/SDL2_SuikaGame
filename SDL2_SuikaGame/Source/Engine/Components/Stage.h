#pragma once
#include <memory>
#include <unordered_set>

#include "Manager/ObjectManager.h"


/// @brief 게임 오브젝트를 담는 스테이지
class Stage : public ObjectManager
{
public:
    Stage() = default;
    virtual ~Stage() = default;

    /// @brief 게임 오브젝트를 업데이트합니다.
    virtual void Update(double delta_time);


    /****** Getter & Setter ******/

    /// @brief 게임 오브젝트를 가져옵니다.
    auto& GetGameObjects() const { return game_objects; }

    /// @brief 새롭게 추가된 게임 오브젝트 목록을 가져옵니다.
    auto& GetNewGameObjects() const { return new_game_objects; }

    /// @brief 새롭게 추가된 게임 오브젝트 목록을 제거합니다.
    void ClearNewGameObjects() { new_game_objects.clear(); }

    /// @brief 새롭게 추가된 이벤트 옵저버 목록을 가져옵니다.
    auto& GetNewEventObservers() const { return new_event_observers; }

    /// @brief 새롭게 추가된 이벤트 옵저버 목록을 제거합니다.
    void ClearNewEventObservers() { new_event_observers.clear(); }
};
