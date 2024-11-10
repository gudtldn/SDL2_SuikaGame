#include "GameEngine.h"
#include "Components/Stage.h"
#include "Components/GameObject.h"

#include <vector>
#include <algorithm>
#include <stdexcept>

#include <SDL.h>


GameEngine::GameEngine(
    const char* title_name,
    int screen_x,
    int screen_y,
    int screen_width,
    int screen_height
)
    : is_running(false)
    , window(nullptr)
    , renderer(nullptr)
    , object_manager(this)
{
    // SDL 미 초기화 시 예외 처리
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        throw std::runtime_error("SDL is not initialized.");
    }

    // SDL 화면 생성
    window = SDL_CreateWindow(
        title_name,
        screen_x, screen_y,
        screen_width, screen_height,
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create window.");
    }

    // SDL 렌더러 생성
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        throw std::runtime_error("Failed to create renderer.");
    }
}

GameEngine::~GameEngine()
{
    // SDL 렌더러 해제
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }

    // SDL 화면 해제
    if (window)
    {
        SDL_DestroyWindow(window);
    }
}

void GameEngine::Run()
{
    is_running = true;

    while (is_running)
    {
        // 이벤트 옵저버 등록
        const auto& new_event_observers = object_manager.GetNewEventObservers();
        if (!new_event_observers.empty())
        {
            for (const auto& observer : new_event_observers)
            {
                event_manager.AddObserver(observer);
            }
            object_manager.ClearNewEventObservers();
        }

        if (current_stage)
        {
            auto& stage_obj_manager = current_stage->GetObjectManager();
            const auto& new_stage_observers = stage_obj_manager.GetNewEventObservers();
            if (!new_stage_observers.empty())
            {
                for (const auto& observer : new_stage_observers)
                {
                    event_manager.AddObserver(observer);
                }
                stage_obj_manager.ClearNewEventObservers();
            }
        }


        // 이벤트 처리
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            event_manager.NotifyObservers(event);
            if (event.type == SDL_QUIT)
            {
                is_running = false;
            }
        }

        // 업데이트
        Update(0.0f); // TODO: delta time 구현

        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 렌더링
        Render();

        // 화면 업데이트
        SDL_RenderPresent(renderer);
    }
}

void GameEngine::Update(double delta_time)
{
    // 새로운 게임 오브젝트의 BeginPlay 호출
    const auto& new_game_objects = object_manager.GetNewGameObjects();
    for (const auto& new_game_object : new_game_objects)
    {
        new_game_object->BeginPlay();
    }
    object_manager.ClearNewGameObjects();

    // 현재 스테이지의 새로운 게임 오브젝트의 BeginPlay 호출
    if (current_stage)
    {
        auto& stage_obj_manager = current_stage->GetObjectManager();
        const auto& new_stage_objects = stage_obj_manager.GetNewGameObjects();
        for (const auto& new_game_object : new_stage_objects)
        {
            new_game_object->BeginPlay();
        }
        stage_obj_manager.ClearNewGameObjects();
    }


    // 현재 스테이지 업데이트
    if (current_stage)
    {
        current_stage->Update(delta_time);
    }

    // 게임 오브젝트 업데이트
    for (const auto& game_object : object_manager.GetGameObjects())
    {
        game_object->Update(delta_time);
    }
}

void GameEngine::Render()
{
    auto& game_objects = object_manager.GetGameObjects();

    std::vector<std::shared_ptr<GameObject>> render_queue; // TODO: 성능 개선 필요, 필요할 때만 할당하도록 수정
    render_queue.reserve(
        game_objects.size()
        + (current_stage ? current_stage->GetObjectManager().GetGameObjects().size() : 0)
    );

    // GameEngine의 Obj를 렌더링큐에 추가
    render_queue.insert(
        render_queue.end(),
        game_objects.begin(),
        game_objects.end()
    );

    // 현재 스테이지의 Obj를 렌더링큐에 추가
    if (current_stage != nullptr)
    {
        const auto& stage_objects = current_stage->GetObjectManager().GetGameObjects();
        render_queue.insert(
            render_queue.end(),
            stage_objects.begin(),
            stage_objects.end()
        );
    }

    // Z-Order로 정렬
    std::sort(
        render_queue.begin(),
        render_queue.end(),
        [](const auto& lhs, const auto& rhs)
        {
            return lhs->GetZOrder() < rhs->GetZOrder();
        }
    );

    // 렌더링
    for (auto& game_object : render_queue)
    {
        game_object->Render(GetRenderer());
    }
}
