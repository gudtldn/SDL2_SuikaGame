#pragma once
#include <memory>
#include <unordered_set>

#include "Engine/Manager/ObjectManager.h"

// forward declaration
class GameEngine;
union SDL_Event;


/// @brief 게임 오브젝트를 담는 스테이지
class Stage
{
private:
    /// @brief 게임 엔진
    GameEngine* engine;

    /// @brief 게임 오브젝트 매니저
    ObjectManager object_manager;

public:
    Stage(GameEngine* engine);
    virtual ~Stage() = default;

    // 복사 & 이동 생성자 삭제
    Stage(const Stage&) = delete;
    Stage& operator=(const Stage&) = delete;
    Stage(Stage&&) = delete;
    Stage& operator=(Stage&&) = delete;

    /// @brief 게임 오브젝트를 초기화합니다.
    virtual void InitializeObjects() = 0;

    /// @brief SDL 이벤트 발생 시 호출됩니다.
    /// @param event SDL 이벤트
    virtual void HandleEvent(const SDL_Event& event);

    /// @brief 게임 오브젝트를 업데이트합니다.
    /// @param delta_time Delta time
    virtual void HandleUpdate(float delta_time);

    /// @brief 고정된 시간만큼 게임 오브젝트를 업데이트합니다.
    /// @param fixed_time 고정된 시간
    virtual void HandleFixedUpdate(float fixed_time);


    /*** Getter & Setter ***/

    /// @brief 게임 오브젝트 매니저를 가져옵니다.
    ObjectManager& GetObjectManager() { return object_manager; }

    /// @brief 게임 엔진을 가져옵니다.
    [[nodiscard]] GameEngine* GetEngine() const { return engine; }
};
