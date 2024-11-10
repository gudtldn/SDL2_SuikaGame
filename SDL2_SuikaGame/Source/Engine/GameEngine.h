#pragma once
#include <memory>
#include <type_traits>

#include "Manager/ObjectManager.h"
#include "Manager/EventManager.h"


// foward declaration
struct SDL_Window;
struct SDL_Renderer;

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


private:
    /// @brief 현재 스테이지
    std::unique_ptr<Stage> current_stage;

    /// @brief 이벤트 관리자
    EventManager event_manager;

    /// @brief 게임 오브젝트 관리자
    ObjectManager object_manager;

    /// @brief 게임이 실행 중인지 여부
    bool is_running;

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

    /// @brief 게임 오브젝트 관리자를 가져옵니다.
    ObjectManager& GetObjectManager() { return object_manager; }

    /// @brief 현재 스테이지를 가져옵니다.
    Stage* GetCurrentStage() const { return current_stage.get(); }

    /// @brief 게임이 실행 중인지 여부를 가져옵니다.
    bool IsRunning() const { return is_running; }


    /****** Method ******/

    /// @brief 게임 오브젝트를 업데이트합니다.
    void Update(double delta_time);

    /// @brief 게임 오브젝트를 렌더링합니다.
    void Render();

    /// @brief 게임을 실행합니다.
    void Run();

    /// @brief 현재 스테이지를 설정합니다.
    /// @tparam S Stage를 상속받은 클래스
    template <typename S>
        requires std::derived_from<S, Stage>
    void SetStage();
};


template <typename S>
    requires std::derived_from<S, Stage>
void GameEngine::SetStage()
{
    current_stage = std::make_unique<S>(this);
}
