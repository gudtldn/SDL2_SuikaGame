#pragma once
#include <memory>
#include <type_traits>
#include <SDL.h>

#include "Engine/AbstractClasses/Stage.h"
#include "Engine/AbstractClasses/GameObject.h"
#include "Engine/Manager/SDLManager.h"
#include "Engine/Manager/ObjectManager.h"
#include "Engine/Manager/ResourceManager.h"
#include "Engine/Utils/Math.h"

// forward declaration
class Stage;
class GameObject;


/// @brief SDL 화면을 관리하는 클래스
class GameEngine
{
private:
    /// @brief SDL 화면
    SDL_Window* window;

    /// @brief SDL 렌더러
    SDL_Renderer* renderer;

    /// @brief 게임 컨트롤러
    SDL_GameController* controller;

private:
    /// @brief 현재 스테이지
    std::unique_ptr<Stage> current_stage;

    /// @brief 게임 오브젝트 관리자
    ObjectManager object_manager;

    /// @brief 게임 리소스 관리자
    ResourceManager resource_manager;

    /// @brief 게임이 실행 중인지 여부
    bool is_running;

    /// @brief 누적 시간
    float accumulated_time;

    /// @brief 고정된 시간
    float fixed_time_v;

    /// @brief 누적 시간 초기화 간격
    static constexpr float RESET_THRESHOLD = 2 * PI;

public:
    /// @brief 화면을 생성하고 초기화합니다.
    /// @param title_name 창 제목
    /// @param screen_x 창 x 좌표
    /// @param screen_y 창 y 좌표
    /// @param screen_width 화면 너비
    /// @param screen_height 화면 높이
    GameEngine(
        const char* title_name,
        int screen_x,
        int screen_y,
        int screen_width,
        int screen_height
    );

    // 이동 & 복사 연산자 제거
    GameEngine(GameEngine&&) = delete;
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;
    GameEngine& operator=(GameEngine&&) = delete;

    /// @brief 사용한 자원을 해제합니다.
    ~GameEngine();


    /****** Getter & Setter ******/

    /// @brief SDL 화면을 가져옵니다.
    SDL_Window* GetWindow() const { return window; }

    /// @brief SDL 렌더러를 가져옵니다.
    SDL_Renderer* GetRenderer() const { return renderer; }

    /// @brief 게임 컨트롤러를 가져옵니다.
    SDL_GameController* GetController() const { return controller; }

    /// @brief 게임 오브젝트 관리자를 가져옵니다.
    ObjectManager& GetObjectManager() { return object_manager; }

    /// @brief 게임 리소스 관리자를 가져옵니다.
    ResourceManager& GetResourceManager() { return resource_manager; }

    /// @brief 현재 스테이지를 가져옵니다.
    Stage* GetCurrentStage() const { return current_stage.get(); }

    /// @brief 게임이 실행 중인지 여부를 가져옵니다.
    bool IsRunning() const { return is_running; }

    /// @brief 누적 시간을 가져옵니다. (sin주기에 따라 초기화됨 0 ~ 2 * PI)
    float GetAccumulatedTime() const { return accumulated_time; }

    /// @brief 고정된 시간을 가져옵니다.
    float GetFixedTime() const { return fixed_time_v; }

    /// @brief 고정된 시간을 설정합니다.
    /// @param time 고정된 시간
    void SetFixedTime(float time) { fixed_time_v = time; }


    /****** Method ******/

    /// @brief 게임을 실행합니다.
    void Run();

    /// @brief 현재 스테이지를 설정합니다.
    /// @tparam S Stage를 상속받은 클래스
    template <typename S>
        requires std::derived_from<S, Stage>
    void SetStage();

private:
    /// @brief 이벤트를 처리합니다.
    /// @param event SDL 이벤트
    inline void HandleEvent(const SDL_Event& event);

    /// @brief 게임 오브젝트를 업데이트합니다.
    inline void Update(float delta_time);

    /// @brief 고정된 시간만큼 게임 오브젝트를 업데이트합니다.
    /// @param fixed_time 고정된 시간
    inline void FixedUpdate(float fixed_time);

    /// @brief 게임 오브젝트를 렌더링합니다.
    inline void Render() const;

    /// @brief 누적 시간을 추가합니다.
    /// @param time 추가할 시간
    inline void AddAccumulatedTime(float time);
};


template <typename S>
    requires std::derived_from<S, Stage>
void GameEngine::SetStage()
{
    // 모든 오브젝트 제거
    if (current_stage)
    {
        auto& game_objects = current_stage->GetObjectManager().GetGameObjects();
        for (auto& object : game_objects)
        {
            // 완전히 삭제하기 전에 OnDestroy()를 호출
            object->OnDestroy();
        }
    }

    // 새로운 스테이지 생성
    current_stage = std::make_unique<S>(this);
    current_stage->InitializeStage();
}
