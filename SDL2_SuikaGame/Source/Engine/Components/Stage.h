#pragma once
#include <memory>
#include <unordered_set>

#include "Manager/ObjectManager.h"

// forward declaration
class GameObject;


/// @brief 게임 오브젝트를 담는 스테이지
class Stage : public ObjectManager
{
protected:
    /// @brief 게임 오브젝트를 담을 집합
    std::unordered_set<std::shared_ptr<GameObject>> game_objects;

public:
    Stage() = default;
    virtual ~Stage() = default;

    /// @brief 게임 오브젝트를 업데이트합니다.
    virtual void Update(double delta_time);


    /****** Getter & Setter ******/

    /// @brief 게임 오브젝트를 가져옵니다.
    auto& GetGameObjects() const { return game_objects; }
};
