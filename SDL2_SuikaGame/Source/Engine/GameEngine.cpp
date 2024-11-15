#include "GameEngine.h"
#include "Engine/Components/Stage.h"
#include "Engine/Components/GameObject.h"
#include "Engine/Utils/Math.h"
#include "GlobalMacro.h"

#include <ctime>
#include <vector>
#include <algorithm>
#include <stdexcept>


GameEngine::GameEngine(
    const char* title_name,
    int screen_x,
    int screen_y,
    int screen_width,
    int screen_height
)
    : window(nullptr)
    , renderer(nullptr)
    , controller(nullptr)
    , object_manager(this)
    , is_running(false)
    , accumulated_time(0.0f)
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

    // SDL GameController 가져오기
    if (SDL_NumJoysticks() > 0)
    {
        controller = SDL_GameControllerOpen(0);
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

    // SDL GameController 해제
    if (controller)
    {
        SDL_GameControllerClose(controller);
    }
}

void GameEngine::Run()
{
    is_running = true;

    // 랜덤 시드 초기화
    Math::RandInit(static_cast<int>(time(nullptr)));

    Uint64 now_time = SDL_GetPerformanceCounter();

    while (is_running)
    {
        // delta_time 계산
        const Uint64 last_time = now_time;
        now_time = SDL_GetPerformanceCounter();

        const float delta_time_sec =
            static_cast<float>(now_time - last_time) / static_cast<float>(SDL_GetPerformanceFrequency());


        // 누적 시간 추가
        AddAccumulatedTime(delta_time_sec);


        // 이벤트 처리
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // 이벤트 처리
            HandleEvent(event);
            if (event.type == SDL_QUIT)
            {
                is_running = false;
            }
        }


        // 업데이트
        Update(delta_time_sec);


        // 화면 지우기
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        // 렌더링
        Render();


        // 화면 업데이트
        SDL_RenderPresent(renderer);


        // TODO: FPS 제한 개선 필요
        // FPS 제한
        // Uint64 frame_end_time = SDL_GetPerformanceCounter();
        // float frame_time = (float)((frame_end_time - now_time) / (float)SDL_GetPerformanceFrequency());
        // if (frame_time < (1.0 / TARGET_FPS))
        // {
        //     SDL_Delay((Uint32)(((1.0 / TARGET_FPS) - frame_time) * 1000.0));
        // }
    }
}

inline void GameEngine::HandleEvent(const SDL_Event& event)
{
    object_manager.HandleEvent(event);

    if (current_stage)
    {
        current_stage->GetObjectManager().HandleEvent(event);
    }
}

inline void GameEngine::Update(float delta_time)
{
    // 새로운 게임 오브젝트의 BeginPlay 호출
    while (GameObject* new_obj = object_manager.PopNewGameObject())
    {
        new_obj->BeginPlay();
    }

    // 현재 스테이지의 새로운 게임 오브젝트의 BeginPlay 호출
    if (current_stage)
    {
        ObjectManager& stage_obj_manager = current_stage->GetObjectManager();
        while (GameObject* new_obj = stage_obj_manager.PopNewGameObject())
        {
            new_obj->BeginPlay();
        }
    }


    // 현재 스테이지 업데이트
    if (current_stage)
    {
        current_stage->GetObjectManager().HandleUpdate(delta_time);
    }

    // 게임 오브젝트 업데이트
    for (const auto& game_object : object_manager.GetGameObjects())
    {
        game_object->Update(delta_time);
    }

    // 물리 시뮬레이션
    box2d_manager.Step(delta_time * 4, 8);
}

inline void GameEngine::Render() const
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
    std::ranges::sort(render_queue, [](const auto& lhs, const auto& rhs)
    {
        return lhs->GetZOrder() < rhs->GetZOrder();
    });

    // 렌더링
    for (const auto& game_object : render_queue)
    {
        game_object->Render(GetRenderer());
    }
}

inline void GameEngine::AddAccumulatedTime(float time)
{
    accumulated_time += time;
    if (accumulated_time >= RESET_THRESHOLD)
    {
        accumulated_time -= RESET_THRESHOLD;
    }
}
