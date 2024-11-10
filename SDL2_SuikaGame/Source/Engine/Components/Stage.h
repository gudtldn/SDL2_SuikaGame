#pragma once
#include <memory>
#include <unordered_set>

#include "Manager/ObjectManager.h"

// forward declaration
class GameEngine;


/// @brief 게임 오브젝트를 담는 스테이지
class Stage
{
private:
    /// @brief 게임 엔진
    GameEngine* engine;

    /// @brief 게임 오브젝트 매니저
    ObjectManager object_manager;

public:
    Stage(GameEngine* engine)
        : engine(engine)
        , object_manager(engine)
    {
    };

    virtual ~Stage() = default;

    /// @brief 게임 오브젝트를 업데이트합니다.
    virtual void Update(double delta_time);

    /*** Getter & Setter ***/
    /// @brief 게임 오브젝트 매니저를 가져옵니다.
    ObjectManager& GetObjectManager() { return object_manager; }

    /// @brief 게임 엔진을 가져옵니다.
    GameEngine* GetEngine() { return engine; }
};
