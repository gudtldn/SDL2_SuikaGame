#pragma once
#include <memory>
#include <unordered_set>

#include "Manager/ObjectManager.h"


/// @brief 게임 오브젝트를 담는 스테이지
class Stage
{
private:
    /// @brief 게임 오브젝트 매니저
    ObjectManager object_manager;

public:
    Stage() = default;
    virtual ~Stage() = default;

    /// @brief 게임 오브젝트를 업데이트합니다.
    virtual void Update(double delta_time);

    /*** Getter & Setter ***/
    /// @brief 게임 오브젝트 매니저를 가져옵니다.
    ObjectManager& GetObjectManager() { return object_manager; }
};
